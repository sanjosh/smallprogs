#include <cstdint>

/** 
 * true false template
 */
template <bool cond, typename A, typename B>
struct if_{
	typedef A type;
};

int main() {
	if_<true, int, char>::type c = 10;
	if_<false, int, char>::type d = 'a';
}

