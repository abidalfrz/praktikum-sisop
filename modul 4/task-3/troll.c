#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <unistd.h>

static const char *file1 = "/very_spicy_info.txt";
static const char *file2 = "/upload.txt";
static const char *flag_path = "/tmp/leak.flag";

const char *ascii_msg =
" ____  ____  __    __      ____  _____  ____    ____  ____      __    ___    __    ____  _  _    ____  ____  _    _    __    ____  ____  \n"
"( ___)( ___)(  )  (  )    ( ___)(  _  )(  _ \\  (_  _)(_  _)    /__\\  / __)  /__\\  (_  _)( \\( )  (  _ \\( ___)( \\/\\/ )  /__\\  (  _ \\(  _ \\ \n"
" )__)  )__)  )(__  )(__    )__)  )(_)(  )   /   _)(_   )(     /(__)\\( (_-. /(__)\\  _)(_  )  (    )   / )__)  )    (  /(__)\\  )   / )(_) )\n"
"(__)  (____)(____)(____)  (__)  (_____)(_)\\_)  (____) (__)   (__)(__)\\___/(__)(__)(____)(_)\\_)  (_)\\_)(____)(__/\\__)(__)(__)(_)\\_)(____/ \n";

int is_trap_active() {
    FILE *f = fopen(flag_path, "r");
    if (f) {
        fclose(f);
        return 1;
    }
    return 0;
}

void set_trap_flag() {
    FILE *f = fopen(flag_path, "w");
    if (f) {
        fprintf(f, "DainTontas has uploaded the leak.\n");
        fclose(f);
    }
}

static int troll_getattr(const char *path, struct stat *stbuf) {
    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (strcmp(path, file1) == 0 || strcmp(path, file2) == 0) {
        stbuf->st_mode = S_IFREG | 0644;
        stbuf->st_nlink = 1;

        const char *username = getpwuid(fuse_get_context()->uid)->pw_name;

        if (is_trap_active() && strstr(path, ".txt")) {
            if (strcmp(username, "DainTontas") == 0) {
                stbuf->st_size = strlen(ascii_msg);
            } else if (strcmp(path, file1) == 0) {
                stbuf->st_size = strlen("DainTontas' personal secret!!.txt\n");
            } else {
                stbuf->st_size = 0;
            }
        } else if (strcmp(path, file1) == 0) {
            const char *username = getpwuid(fuse_get_context()->uid)->pw_name;
            if (strcmp(username, "DainTontas") == 0) {
                stbuf->st_size = strlen("Very spicy internal developer information: leaked roadmap.docx\n");
            } else {
                stbuf->st_size = strlen("DainTontas' personal secret!!.txt\n");
            }
        } else {
            stbuf->st_size = 0;
        }
    } else {
        return -ENOENT;
    }

    return 0;
}

static int troll_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi) {
    if (strcmp(path, "/") != 0) return -ENOENT;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, "very_spicy_info.txt", NULL, 0);
    filler(buf, "upload.txt", NULL, 0);

    return 0;
}

static int troll_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi) {
    (void) fi;
    const char *content = NULL;
    size_t len;

    const char *username = getpwuid(fuse_get_context()->uid)->pw_name;

    if (is_trap_active() && strstr(path, ".txt")) {
        if (strcmp(username, "DainTontas") == 0) {
            content = ascii_msg;
        } else if (strcmp(path, file1) == 0) {
            content = "DainTontas' personal secret!!.txt\n";
        } else {
            content = "";
        }
    } else if (strcmp(path, file1) == 0) {
        if (strcmp(username, "DainTontas") == 0) {
            content = "Very spicy internal developer information: leaked roadmap.docx\n";
        } else {
            content = "DainTontas' personal secret!!.txt\n";
        }
    } else if (strcmp(path, file2) == 0) {
        content = "";
    }

    if (content) {
        len = strlen(content);
        if (offset < len) {
            if (offset + size > len) size = len - offset;
            memcpy(buf, content + offset, size);
        } else {
            size = 0;
        }
        return size;
    }

    return -ENOENT;
}

static int troll_write(const char *path, const char *buf, size_t size,
                       off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    if (strcmp(path, file2) == 0) {
        set_trap_flag();
        return size;
    }
    return -EACCES;
}

static int troll_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    if (strcmp(path, file2) == 0) {
        return 0; 
    }
    return -EACCES;
}

static int troll_open(const char *path, struct fuse_file_info *fi) {
    if (strstr(path, ".txt")) {
        return 0;
    }
    return -EACCES;
}

static int troll_truncate(const char *path, off_t size) {
    if (strcmp(path, file2) == 0) {
        return 0;
    }
    return -EACCES;
}

static struct fuse_operations troll_oper = {
    .getattr  = troll_getattr,
    .readdir  = troll_readdir,
    .read     = troll_read,
    .write    = troll_write,
    .create   = troll_create,
    .open     = troll_open,
    .truncate = troll_truncate,
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &troll_oper, NULL);
}
