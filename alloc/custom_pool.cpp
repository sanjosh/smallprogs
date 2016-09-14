#include <jemalloc/jemalloc.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <sys/mman.h>

extent_hooks_t *old_hooks;

void *
extent_alloc(extent_hooks_t* a, void *new_addr, size_t size, size_t alignment, 
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

bool
extent_dalloc(extent_hooks_t *extent_hooks, void *addr, size_t size,
    bool committed, unsigned arena_ind)
{
	return (old_hooks->dalloc(old_hooks, addr, size, committed, arena_ind));
}

/*
static bool
extent_commit(extent_hooks_t *extent_hooks, void *addr, size_t size,
    size_t offset, size_t length, unsigned arena_ind)
{
	return old_hooks->commit(old_hooks, addr, size, offset, length,
	    arena_ind);
}

static bool
extent_decommit(extent_hooks_t *extent_hooks, void *addr, size_t size,
    size_t offset, size_t length, unsigned arena_ind)
{
	return old_hooks->decommit(old_hooks, addr, size, offset, length,
	    arena_ind);
}

static bool
extent_purge(extent_hooks_t *extent_hooks, void *addr, size_t size,
    size_t offset, size_t length, unsigned arena_ind)
{
	return (old_hooks->purge(old_hooks, addr, size, offset, length,
	    arena_ind));
}

static bool
extent_split(extent_hooks_t *extent_hooks, void *addr, size_t size,
    size_t size_a, size_t size_b, bool committed, unsigned arena_ind)
{
	return old_hooks->split(old_hooks, addr, size, size_a, size_b, committed,
	    arena_ind);
}

static bool
extent_merge(extent_hooks_t *extent_hooks, void *addr_a, size_t size_a,
    void *addr_b, size_t size_b, bool committed, unsigned arena_ind)
{
	return old_hooks->merge(old_hooks, addr_a, size_a, addr_b, size_b,
	    committed, arena_ind);
}
*/

extent_hooks_t hooks = { 
  extent_alloc,
  extent_dalloc,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};  

unsigned alloc_arena()
{
  unsigned arena_number;

  extent_hooks_t* new_hooks = &hooks;
  size_t hooks_len;

  size_t sz = sizeof(arena_number);

  int ret = mallctl("arenas.extend", &arena_number, &sz, nullptr, 0);
  std::cout << "ret=" << ret << ":arena=" << arena_number << std::endl;

  std::string arenaName = "arena." + std::to_string(arena_number) + ".extent_hooks";

  hooks_len = sizeof(extent_hooks_t*);
  ret = mallctl(arenaName.c_str(), &old_hooks, &hooks_len, nullptr, 0);
  assert(ret == 0);
  
  ret = mallctl(arenaName.c_str(), nullptr, nullptr, &new_hooks, hooks_len);
  assert(ret == 0);

  return arena_number;
}

int main(int argc, char* argv[])
{
  unsigned arena_number[2];
  for (int i = 0; i < 2; i++)
  {
    arena_number[i] = alloc_arena();
  }


  for (int i = 0; i < 5; i++)
  {
    // do not allocate from thread local cache
    void* p2 = mallocx(1024, MALLOCX_TCACHE_NONE | MALLOCX_ARENA(arena_number[1]));
    std::cout << "norm malloc=" << (void*)p2 << std::endl;
  }

  for (int i = 0; i < 5; i++)
  {
    void* p = mallocx(1024, MALLOCX_ARENA(0));
    std::cout << "mmap malloc=" << (void*)p << std::endl;
  }
}
