#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void defer_UNIXFD(int* fdp)
{
    close(*fdp);
}

void defer_FILE(FILE **fpp)
{
    fclose(*fpp);
}

typedef int UNIXFD;
#define DEFER(TYPE, var) TYPE var __attribute__((cleanup(defer_ ## TYPE)))
#define DEFER_PTR(TYPE, var) TYPE *var __attribute__((cleanup(defer_ ## TYPE)))

void func()
{
  DEFER_PTR(FILE, fp) = fopen("./afile", "w+");
  DEFER(UNIXFD, fd) = open("./bfile", O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  return;
}

int main()
{
    func();
}
