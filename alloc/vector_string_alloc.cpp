/**
 * g++ -std=c++11 or c++14
 */
#include <cstdint>
#include <limits>
#include <vector>
#include <iostream>
#include <string>

template <class T>
class Arena {
	public:
	size_t num_allocs_{0};

	Arena() noexcept {
  		std::cout << "ctor arena " << (void*)this << std::endl;
	}
	~Arena() {
  		std::cout << "dtor arena " << (void*)this << std::endl;
	}
	Arena(const Arena&) = delete;
	Arena& operator = (const Arena&) = delete;
	
	char* allocate(size_t n) {
	   // print message and allocate memory with global new
	   char* ret = (char*)(::operator new(n * sizeof(T)));
	   num_allocs_ ++;
  		std::cout << "alloc " << (void*)this << std::endl;
	   return ret;
	}
	char* deallocate(char* p, size_t n) noexcept {
	   // print message and deallocate memory with global delete
  		std::cout << "dealloc " << (void*)this << std::endl;
	   num_allocs_ --;
	   ::operator delete((void*)p);
	}
};

template <class T>
class MemoryMappedAlloc {

 public:
   // type definitions
   typedef T        value_type;
   typedef T*       pointer;
   typedef const T* const_pointer;
   typedef T&       reference;
   typedef const T& const_reference;
   typedef std::size_t    size_type;
   typedef std::ptrdiff_t difference_type;

   using arena_type = Arena<T>;

   arena_type& a_; // how u share arena between multiple allocators

   // rebind allocator to type U
   template <class U>
   struct rebind {
       typedef MemoryMappedAlloc<U> other;
   };  

   // return address of values
   pointer address (reference value) const {
	   return &value;
   }
   const_pointer address (const_reference value) const {
	   return &value;
   }

   /* constructors and destructor
	* - nothing to do because the allocator has no state
	*/
   MemoryMappedAlloc(arena_type& a):  a_(a) {
   	//std::cout << "ctor with arena this=" << (void*)this << std::endl;
   }
   MemoryMappedAlloc(const MemoryMappedAlloc& other) : a_(other.a_) {
   	//std::cout << "copy ctor this=" << (void*)this << ",arena=" << (void*)&a_ << std::endl;
   }
   ~MemoryMappedAlloc() throw() {
   	//std::cout << "dtor this=" << (void*)this << std::endl;
   }

   // return maximum number of elements that can be allocated
   size_type max_size () const throw() {
	   return std::numeric_limits<std::size_t>::max() / sizeof(T);
   }

   // allocate but don't initialize num elements of type T
   pointer allocate (size_type num, const void* = 0) {
   	return reinterpret_cast<T*>(a_.allocate(num * sizeof(T)));
   }

   // deallocate storage p of deleted elements
   void deallocate (pointer p, size_type num) {
   	a_.deallocate(reinterpret_cast<char*>(p), num * sizeof(T));
   }

   // initialize elements of allocated storage p with value value
   void construct (pointer p, const T& value) {
	   // initialize memory with placement new
	   new((void*)p)T(value);
   }

   // destroy elements of initialized storage p
   void destroy (pointer p) {
	   // destroy objects by calling their destructor
	   p->~T();
   }
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator== (const MemoryMappedAlloc<T1>&,
				const MemoryMappedAlloc<T2>&) throw() {
   return true;
}
template <class T1, class T2>
bool operator!= (const MemoryMappedAlloc<T1>&,
				const MemoryMappedAlloc<T2>&) throw() {
   return false;
}

typedef std::basic_string<char, std::char_traits<char>, MemoryMappedAlloc<char>> MString;
typedef std::vector<MString, MemoryMappedAlloc<MString>> MVector;

int main() {

	MVector::allocator_type::arena_type ma;
	MString::allocator_type::arena_type string_alloc;

	{
		MVector avec{ma};
	
		for (int i = 0; i < 3; i++) {
			// for small strings lt 16 bytes, allocation is inline
			avec.emplace_back(16, 'a' + (i % 26), string_alloc);
			std::cout << "string arena=" << string_alloc.num_allocs_ << std::endl;
		}

		std::cout << "vector arena=" << ma.num_allocs_ << std::endl;

		for (auto& elem : avec) {
			std::cout << elem << std::endl;
		}
	}
}

