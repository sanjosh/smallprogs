
/*
 * Library interposer for XOpenDisplay() and XCloseDisplay.
 * cc -g -o XOpenDisplay_interpose.so -G -Kpic XOpenDisplay_interpose.c
 * setenv LD_PRELOAD $cwd/XOpenDisplay_interpose.so
 * run the app
 * unsetenv LD_PRELOAD
 */

#include <stdio.h>
#include <X11/Xlib.h>
#include <dlfcn.h>

Display *XOpenDisplay(char *display_name)
{
  static Display * (*func)(char *);
  Display *ret;
 
  if(!func)
    func = (Display *(*)(char *))dlsym(RTLD_NEXT, "XOpenDisplay");

  if(display_name)
    printf("XOpenDisplay() is called with display_name=%s\n", display_name);
  else
    printf("XOpenDisplay() is called with display_name=NULL\n");
/*
  ret = func(display_name);
*/
  printf("  calling XOpenDisplay(NULL)\n");
  ret = func(0);
  printf("XOpenDisplay() returned %p\n", ret);

  return(ret);
}

int XCloseDisplay(Display *display_name)
{ 
  static int (*func)(Display *); 
  int ret; 
  
  if(!func)
    func = (int (*)(Display *))dlsym(RTLD_NEXT, "XCloseDisplay"); 
 
  ret = func(display_name); 
 
  printf("called XCloseDisplay(%p)\n", display_name); 
 
  return(ret); 
}
