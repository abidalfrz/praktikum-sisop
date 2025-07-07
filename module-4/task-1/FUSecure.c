#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h> 

const char *source_dir = "/home/nabila/shared_files";

static void full_path(char fpath[PATH_MAX], const char *path) {
    snprintf(fpath, PATH_MAX, "%s%s", source_dir, path);
}

static int fs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                      off_t offset, struct fuse_file_info *fi) {
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, "public", NULL, 0);
    filler(buf, "private_yuadi", NULL, 0);
    filler(buf, "private_irwandi", NULL, 0);
    return 0;
}

static int fs_getattr(const char *path, struct stat *stbuf) {
    char fpath[PATH_MAX];
    full_path(fpath, path);
    int res = lstat(fpath, stbuf);
    if (res == -1) return -errno;
    return 0;
}

static int fs_open(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    full_path(fpath, path);

    if (strncmp(path, "/private_yuadi/", 15) == 0 && fuse_get_context()->uid != getpwnam("yuadi")->pw_uid) {
        return -EACCES;
    }

    if (strncmp(path, "/private_irwandi/", 17) == 0 && fuse_get_context()->uid != getpwnam("irwandi")->pw_uid) {
        return -EACCES;
    }

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) return -errno;

    close(fd);
    return 0;
}

static int fs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    full_path(fpath, path);

    int fd = open(fpath, O_RDONLY);
    if (fd == -1) return -errno;

    int res = pread(fd, buf, size, offset);
    if (res == -1) res = -errno;

    close(fd);
    return res;
}

static int fs_mkdir(const char *path, mode_t mode) {
    return -EROFS;
}

static int fs_rmdir(const char *path) {
    return -EROFS;
}

static int fs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    return -EROFS;
}

static int fs_unlink(const char *path) {
    return -EROFS;
}

static int fs_write(const char *path, const char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi) {
    return -EROFS;
}

static int fs_rename(const char *from, const char *to) {
    return -EROFS;
}

static int fs_truncate(const char *path, off_t size) {
    return -EROFS;
}

static struct fuse_operations fs_oper = {
    .readdir = fs_readdir,
    .getattr = fs_getattr,
    .mkdir   = fs_mkdir,
    .rmdir   = fs_rmdir,
    .create  = fs_create,
    .unlink  = fs_unlink,
    .write   = fs_write,
    .rename  = fs_rename,
    .truncate= fs_truncate,
    .open    = fs_open,
    .read    = fs_read
};

int main(int argc, char *argv[]) {
    umask(0);
    return fuse_main(argc, argv, &fs_oper, NULL);
}
