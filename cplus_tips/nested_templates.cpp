
#include <vector>
#include <cstdlib>
#include <memory>

/**
 * nested templates
 */

template <
	typename K,
	template <typename T, typename Alloc = std::allocator<T>> class Container,
	template <
		typename T, 
		typename Destructor = std::default_delete<T>
		> class Ref,
	typename = typename std::enable_if<std::is_same<int, K>::value>::type 
	>
class Stack {

	public:

	Container<K> a; 
	Ref<K> b;
	Ref<Container<K>> c;
	Container<Ref<Container<K>>> d;

};

struct Dummy {
};

int main()
{
	Stack<int, std::vector, std::unique_ptr> b;
#ifdef WONT_COMPILE
	Stack<Dummy, std::unique_ptr, std::vector> b; // wont compile
	Stack<double, std::unique_ptr, std::vector> b; // wont compile
#endif
}
