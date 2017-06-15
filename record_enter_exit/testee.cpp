#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

extern "C" void __cyg_profile_func_enter(void* func, void* callsite) __attribute__((no_instrument_function));
extern "C" void __cyg_profile_func_exit(void* func, void* callsite) __attribute__((no_instrument_function));

extern "C" void __cyg_profile_func_enter(void* func, void* callsite) 
{
	Dl_info dlinfo;
	int ret = dladdr(func, &dlinfo);
	printf("enter %d %s %s\n", ret, dlinfo.dli_fname, dlinfo.dli_sname);
}

extern "C" void __cyg_profile_func_exit(void* func, void* callsite) 
{
	Dl_info dlinfo;
	int ret = dladdr(func, &dlinfo);
	printf("exit %d %s %s\n", ret, dlinfo.dli_fname, dlinfo.dli_sname);
}

extern "C" int afunc();

int main()
{
	afunc();
}
