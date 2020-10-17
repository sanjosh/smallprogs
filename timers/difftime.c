
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        exit(1);
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    struct stat stbuf;
    int rc = stat(argv[1], &stbuf);

    time_t t = time(NULL); 
    if (t != (time_t)-1) {
        double d;

        d = difftime(t, stbuf.st_mtime);
        printf("mtime %f\n", d);

        d = difftime(t, stbuf.st_atime);
        printf("atime %f\n", d);

        d = difftime(t, stbuf.st_ctime);
        printf("ctime %f\n", d);
    }
}
