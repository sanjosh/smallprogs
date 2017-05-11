
#include "AllocatorWithStats.h"
#include <vector>

struct Elem {
	int a;
	char b[12];
	int c;
};

int main()
{
	std::vector<Elem, AllocatorWithStats<Elem>> a;
	
	Elem e;
	a.push_back(e);
	
	// returns a copy unfortunately
	// http://stackoverflow.com/questions/15851888/why-does-stdvectorget-allocator-return-by-value
	const auto& alloc = a.get_allocator();
}
