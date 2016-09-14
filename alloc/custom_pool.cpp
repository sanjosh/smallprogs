#include <jemalloc/jemalloc.h>
#include <iostream>
#include <string.h>
#include <sys/mman.h>


void *alloc_mmap(void *new_addr, size_t size, size_t alignment, 
    bool *zero, bool *commit, unsigned arena_ind)
{
  void *p = mmap(nullptr, size, PROT_READ | PROT_WRITE, 
      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 
  std::cout << "MMAP=" << p << ":arena=" << arena_ind << ":size=" << size << std::endl;
  if (*zero) {
    bzero(p, size);
    *zero = false;
  }
  *commit = true;
  return p;
}

int main(int argc, char* argv[])
{
    int ret = 0;

    unsigned arena_number;
    {
      chunk_hooks_t old_hooks;
      chunk_hooks_t new_hooks;
      size_t hooks_len;

      size_t sz = sizeof(arena_number);

      ret = mallctl("arenas.extend", &arena_number, &sz, nullptr, 0);
      std::cout << "ret=" << ret << ":arena=" << arena_number << std::endl;

      std::string arenaName = "arena." + std::to_string(arena_number) + ".chunk_hooks";

      hooks_len = sizeof(old_hooks);
      ret = mallctl(arenaName.c_str(), &old_hooks, &hooks_len, nullptr, 0);
      std::cout << "ret=" << ret << std::endl;
      
      new_hooks = old_hooks;
      new_hooks.alloc = alloc_mmap;

      ret = mallctl(arenaName.c_str(), nullptr, nullptr, &new_hooks, hooks_len);
      std::cout << "ret=" << ret << std::endl;
    }


    for (int i = 0; i < 5; i++)
    {
      void* p = mallocx(1024, MALLOCX_ARENA(arena_number));
      std::cout << "mmap malloc=" << (void*)p << std::endl;
    }
    for (int i = 0; i < 5; i++)
    {
      void* p2 = mallocx(1024, MALLOCX_ARENA(0));
      std::cout << "norm malloc=" << (void*)p2 << std::endl;
    }

}
