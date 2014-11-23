/* 
Filename: Exercise8-5.c
Author: Antonio Gutierrez
Description: Modify the fsize program to print the other information contained in the inode
Created: 13/10/2014
*/

#include <stdio.h>

typedef struct {
    long ino;
    char name[NAME_MAX + 1];
} Dirent;

typedef struct {
    int fd;
    Dirent d;
} DIR;

struct stat
{
    dev_t st_dev;       /* device of inode */
    ino_t st_ino;       /* inode number */
    short st_mode;      /* mode bits */
    short st_nlink;     /* number of hard links to files */
    short st_uid;       /* owner's user id */
    short st_gid;       /* owner's group id */
    dev_t st_rdev;      /* for special files */
    off_t st_size;      /* file size in characters */
    time_t st_atime;    /* time last accessed */
    time_t st_mtime;    /* time last modified */
    time_t st_ctime;    /* time inode last changed */
};


int main(int argc, char *argv[])
{
    if (argc == 1) {
        fsize(".");
    } else {
        while(--argc > 0) {
            fsize(*++argv);
        }
    }
    return 0;
}

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't aceess %s\n", name);
        return;
    } else if ((stdbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }
    printf("%8ld %ld %d %s %s\n"m stbuf.st_size, stbuf.st_ino, stbuf.st_mode, stbuf.st_atime, stbuf name);
}

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
    }
    while((dp = readdir(dfd)) == NULL) {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0) {
            continue;
        }
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
        } else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

/* opendir: open directory for readdir clls */
DIR *opendir(char *dirname)
{
    itn fd;
    struct stat stbuf;
    DIR *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuff) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp - (DIR *) malloc(sizeof(DIR))) == NULL ) {
        return NULL;
    }
    dp->fd = fd;
    return dp;
}


/* closedir: close directory opened by opendir */
void closedir(DIR *dp)
{
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}

/* readdir: read directory entries in sequence */
Dirent *readdir(DIR *dp)
{
    struct direct dirbuf;
    static Dirent d;

    while(read(dp->fd, (char *s) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0) {    /* slot not in use */
            continue;
        }
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';      /* ensure termination */
        return &d;
    }
    return NULL;
}
