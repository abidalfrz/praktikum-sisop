#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

static const char *dirpath = "/home/pardofelis/Praktikum4/LawakFS++";
static const char *logpath = "/home/pardofelis/Praktikum4/var/log/lawakfs.log";

char secret_basename[256] = "secret";
int start_hour = 8, start_minute = 0;
int end_hour = 23, end_minute = 0;
char *filter_words[100]; 
int filter_word_count = 0;

void parse_time(const char *time_str, int *hour, int *minute) {
    sscanf(time_str, "%2d:%2d", hour, minute);
}

void load_config() {
    char config_path[1024];
    sprintf(config_path, "/home/pardofelis/Praktikum4/LawakFS++/lawak.conf");

    FILE *config = fopen(config_path, "r"); 
    if (!config) {
        fprintf(stderr, "Could not open config file: %s\n", config_path);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), config)) {
        if (strncmp(line, "START=", 6) == 0) {
            parse_time(line + 6, &start_hour, &start_minute);
        } else if (strncmp(line, "END=", 4) == 0) {
            parse_time(line + 4, &end_hour, &end_minute);
        } else if (strncmp(line, "SECRET_FILE_BASENAME=", 22) == 0) {
            sscanf(line + 22, "%s", secret_basename);
        } else if (strncmp(line, "FILTER_WORDS=", 13) == 0) {
            char *token = strtok(line + 13, ",\n");
            while (token && filter_word_count < 100) {
                filter_words[filter_word_count++] = strdup(token);
                token = strtok(NULL, ",\n");
            }
        }
    }

    fclose(config);
}

void write_log(const char *fuse_path, const char *action) {
    FILE *log_file = fopen(logpath, "a");
    if (!log_file) return;

    time_t rawtime;
    struct tm *timeinfo;
    char time_str[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);

    uid_t uid = getuid();

    fprintf(log_file, "[%s] [%d] [%s] [%s]\n", time_str, uid, action, fuse_path);
    fclose(log_file);
}

int is_outside_working_hours() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    int now = tm_info->tm_hour * 60 + tm_info->tm_min;
    int start = start_hour * 60 + start_minute;
    int end = end_hour * 60 + end_minute;

    return now < start || now >= end;
}

int is_secret_file(const char *filename) {
    return strcmp(filename, secret_basename) == 0;
}

static int xmp_getattr(const char *path, struct stat *stbuf) {
    int res;
    char real_path[1024];

    if (strcmp(path, "/") == 0) {
        sprintf(real_path, "%s", dirpath);
        res = lstat(real_path, stbuf);
        if (res == -1) return -errno;
        return 0;
    }

    char *filename = strrchr(path, '/');
    filename = filename ? filename + 1 : (char *)path;

    if (is_outside_working_hours() && is_secret_file(filename)) return -ENOENT;
    sprintf(real_path, "%s%s", dirpath, path);

    res = lstat(real_path, stbuf);
    if (res == -1) return -errno;
    return 0;
}

static int xmp_access(const char *path, int mask) {
    char real_path[1024];

    if (strcmp(path, "/") == 0) return access(dirpath, mask);

    char *filename = strrchr(path, '/');
    filename = filename ? filename + 1 : (char *)path;

    if (is_outside_working_hours() && is_secret_file(filename)) return -ENOENT;
    sprintf(real_path, "%s%s", dirpath, path);

    if (access(real_path, mask) == 0) {
        write_log(path, "ACCESS");
        return 0;
    }

    return -errno;
}

static int xmp_open(const char *path, struct fuse_file_info *fi) {
    char real_path[1024];

    if (strcmp(path, "/") == 0) return -EISDIR;

    char *filename = strrchr(path, '/');
    filename = filename ? filename + 1 : (char *)path;

    if (is_outside_working_hours() && is_secret_file(filename)) return -ENOENT;
    sprintf(real_path, "%s%s", dirpath, path);

    int fd = open(real_path, O_RDONLY);
    if (fd == -1) return -errno;
    close(fd);

    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char real_path[1024];
    char *filename = strrchr(path, '/');
    filename = filename ? filename + 1 : (char *)path;

    if (is_outside_working_hours() && is_secret_file(filename)) return -ENOENT;
    sprintf(real_path, "%s%s", dirpath, path);

    FILE *file = fopen(real_path, "rb");
    if (!file) return -errno;

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fsize <= 0) {
        fclose(file);
        return 0;
    }

    unsigned char *content = malloc(fsize);
    fread(content, 1, fsize, file);
    fclose(file);

    int is_binary = 0;
    for (long i = 0; i < fsize; i++) {
        if (content[i] == 0) {
            is_binary = 1;
            break;
        }
    }

    char *result_buf = NULL;
    int result_len = 0;

    if (is_binary) {
        BIO *bio, *b64;
        BUF_MEM *bptr;

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new(BIO_s_mem());
        bio = BIO_push(b64, bio);

        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
        BIO_write(bio, content, fsize);
        BIO_flush(bio);
        BIO_get_mem_ptr(bio, &bptr);

        result_buf = malloc(bptr->length + 1);
        memcpy(result_buf, bptr->data, bptr->length);
        result_buf[bptr->length] = '\0';
        result_len = bptr->length;

        BIO_free_all(bio);
    } else {
        result_buf = malloc(fsize + 1);
        memcpy(result_buf, content, fsize);
        result_buf[fsize] = '\0';
        result_len = fsize;
    }

    free(content);

    size_t final_buf_size = result_len * 2;
    char *final_buf = malloc(final_buf_size);
    char *src = result_buf;
    char *dst = final_buf;

    while (*src) {
        int replaced = 0;
        for (int i = 0; i < filter_word_count; i++) {
            size_t len_target = strlen(filter_words[i]);
            if (strncmp(src, filter_words[i], len_target) == 0) {
                memcpy(dst, "lawak", 5);
                dst += 5;
                src += len_target;
                replaced = 1;
                break;
            }
        }
        if (!replaced) {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    result_len = dst - final_buf;

    free(result_buf);
    result_buf = final_buf;

    if (offset < result_len) {
        if (offset + size > result_len)
            size = result_len - offset;
        memcpy(buf, result_buf + offset, size);
    } else {
        size = 0;
    }

    write_log(path, "READ");
    free(result_buf);
    return size;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    DIR *dp;
    struct dirent *de;
    char fpath[1024];

    if (strcmp(path, "/") == 0) {
        sprintf(fpath, "%s", dirpath);
    } else {
        sprintf(fpath, "%s%s", dirpath, path);
    }

    dp = opendir(fpath);
    if (dp == NULL) return -errno;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    while ((de = readdir(dp)) != NULL) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;

        char name_only[1024];
        strncpy(name_only, de->d_name, sizeof(name_only) - 1);
        name_only[sizeof(name_only) - 1] = '\0';

        char *dot = strrchr(name_only, '.');
        if (dot != NULL && dot != name_only) {
            *dot = '\0';
        }

        if (is_outside_working_hours() && is_secret_file(name_only)) continue;

        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;

        if (filler(buf, name_only, &st, 0)) break;
    }

    closedir(dp);
    return 0;
}

static int announcement() {
    return -EROFS;
}

static struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .readdir = xmp_readdir,
    .read = xmp_read,
    .open = xmp_open,
    .access = xmp_access,
    .write = announcement,
    .truncate = announcement,
    .create = announcement,
    .unlink = announcement,
    .mkdir = announcement,
    .rmdir = announcement,
    .rename = announcement,
};

int main(int argc, char *argv[]) {
    umask(0);
    load_config();
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
