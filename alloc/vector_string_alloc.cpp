/**
 * g++ -std=c++11 or c++14
 */
#include <cstdint>
#include <limits>
#include <string.h>
#include <vector>
#include <iostream>
#include <string>

template <class T>
class Arena {

	public:

	std::string name_;
	std::vector<size_t> slots_;
	char* buffer_;
	size_t bufferSize_{1048576};
	size_t end_{0};
	size_t num_allocs_{0};

	Arena(const std::string& name) noexcept {
		name_ = name;
		buffer_ = new char[bufferSize_];
	}

	~Arena() {
		free(buffer_);
	}

	Arena(const Arena& other) {
		name_ = other.name_;
		slots_ = other.slots_;
		buffer_ = (char*)malloc(bufferSize_);
		memcpy(buffer_, other.buffer_, other.end_);
		end_ = other.end_;
		num_allocs_ = other.num_allocs_;
	}

	Arena& operator = (const Arena&) = delete;
	
	char* allocate(size_t n) {
	   // print message and allocate memory with global new
	   size_t req_size = n * sizeof(T);
	   char* ret = buffer_ + end_;
	   end_ += req_size;
	   slots_.push_back(req_size);
	   num_allocs_ ++;
	   std::cout << "alloc=" << name_ << ",num=" << num_allocs_ << std::endl;
	   return ret;
	}
	void deallocate(char* p, size_t n) noexcept {
	   // print message and deallocate memory with global delete
	   num_allocs_ --;
	   std::cout << "dealloc=" << name_ << ",num=" << num_allocs_ << std::endl;
	}

	void save(const std::string& filename) {

		//json_t save_json = json_object();
		//int rc = json_object_set_new(save_json, 

		std::cout << name_ << "," << (void*)buffer_ << "," << end_ << std::endl;
		size_t start = 0;
		for (auto slot : slots_) {
			std::cout << slot << "," << (char*)buffer_ + start << std::endl;
			start += slot;
		}
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
   }
   MemoryMappedAlloc(const MemoryMappedAlloc& other) : a_(other.a_) {
   }
   ~MemoryMappedAlloc() throw() {
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

	MString::allocator_type::arena_type string_alloc("string");
	MVector::allocator_type::arena_type vector_alloc("vector");

	MVector avec(vector_alloc);
	avec.reserve(3);
	{
		for (int i = 0; i < 3; i++) {
			// for small strings lt 16 bytes, allocation is inline
			avec.emplace_back(i + 14, 'a' + (i % 26), string_alloc);
		}
		//vector_alloc.save();
		//string_alloc.save();
	}

	{
		MVector bvec(vector_alloc);
		memcpy(&bvec, &avec, sizeof(avec));
		std::cout << "bvec=" << bvec.size() << std::endl;
		for (int i = 0; i < 3; i++) {
			// for small strings lt 16 bytes, allocation is inline
			std::cout << bvec[i] << std::endl;
		}
	}
}

