
/* Example of a library interposer: interpose on malloc().
 * Build and use this interposer as following:
 * cc -o malloc_interposer.so -G -Kpic malloc_interposer.c
 * setenv LD_PRELOAD $cwd/malloc_interposer.so
 * run the app
 * unsetenv LD_PRELOAD
 */

#define _GNU_SOURCE // to enable RTLD_NEXT on linux

#include <stdio.h>
#include <dlfcn.h>

// gcc -o malloc_interposer.so -fPIC malloc_interposer.c -shared


void *malloc(size_t size)
{
  static void * (*func)();

  if(!func)
    func = (void *(*)()) dlsym(RTLD_NEXT, "malloc");
  printf("malloc(%d) is called\n", size);     
  return(func(size));
}

