/**
 * http://howardhinnant.github.io/stack_alloc.html
 */

#include "short_alloc.h"
#include <iostream>
#include <new>
#include <vector>

// Replace new and delete just for the purpose of demonstrating that
//  they are not called.

std::size_t memory = 0;
std::size_t alloc = 0;

void* operator new(std::size_t s) throw(std::bad_alloc)
{
    memory += s;
    ++alloc;
    return malloc(s);
}

void  operator delete(void* p) throw()
{
    --alloc;
    free(p);
}

void memuse()
{
    std::cout << "memory = " << memory << '\n';
    std::cout << "alloc = " << alloc << '\n';
}

// Create a vector<T> template with a small buffer of 200 bytes.
//   Note for vector it is possible to reduce the alignment requirements
//   down to alignof(T) because vector doesn't allocate anything but T's.
//   And if we're wrong about that guess, it is a compile-time error, not
//   a run time error.
template <class T, std::size_t BufSize = 200>
using SmallVector = std::vector<T, short_alloc<T, BufSize, alignof(T)>>;

template <class T, std::size_t BufSize = 200>
using SmallList = std::list<T, short_alloc<T, BufSize>>;

template <class T, std::size_t BufSize = 200>
using SmallSet = std::unordered_set<T, std::hash<T>, std::equal_to<T>,
                      short_alloc<T, BufSize, alignof(T) < 8 ? 8 : alignof(T)>>;

int main()
{
	{
    	// Create the stack-based arena from which to allocate
    	SmallVector<int>::allocator_type::arena_type a;
    	// Create the vector which uses that arena.
    	SmallVector<int> v{a};
    	// Exercise the vector and note that new/delete are not getting called.
    	v.push_back(1);
    	memuse();
    	v.push_back(2);
    	memuse();
    	v.push_back(3);
    	memuse();
    	v.push_back(4);
    	memuse();
    	// Yes, the correct values are actually in the vector
    	for (auto i : v)
        	std::cout << i << ' ';
    	std::cout << '\n';
	}

	{
		SmallList<int>::allocator_type::arena_type a;
		SmallList<int> v{a};
		v.push_back(1);
		memuse();
		v.push_back(2);
		memuse();
		v.push_back(3);
		memuse();
		v.push_back(4);
		memuse();
		for (auto i : v)
			std::cout << i << ' ';
		std::cout << '\n';
	}

}

