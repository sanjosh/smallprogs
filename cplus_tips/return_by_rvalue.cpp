#include <iostream>
#include <map>
#include <string>

/**
 * putting rvalue in return type can cause garbage
 * because destructor of source is called before move constructor
 */

class Dlass
{
	public:
	explicit Dlass(int32_t val) {
		std::cout << "ctor=" << (void*)this << std::endl;
		a = val;
	}
	Dlass(const Dlass& other) {
		std::cout << "copy ctor" << std::endl;
		a = other.a;
	}
	Dlass(Dlass&& other) {
		std::cout << "move ctor " << (&other) << ",val=" << other.a << std::endl;
		a = other.a;
		other.a = -1;
	}
	~Dlass() {
		std::cout << "dtor=" << (void*)this << std::endl;
	}
	int32_t a {-1};
};

// if u dont remove the rvalue in the signature, value becomes garbage 
// because tmp is destroyed before move constructor
Dlass&& getMovedWithReturn()
{
	Dlass tmp(3);
	return std::move(tmp);
}

Dlass func1()
{
	return getMovedWithReturn();
}

// Second version of same func which prints var nicely 
// because move constructor called before destructor
Dlass getMoved()
{
	Dlass tmp(4);
	return std::move(tmp);
	// if u std::move, move ctor wont get called explicitly
	// but RVO ensures obj gets moved
}

Dlass func2()
{
	return getMoved();
}

int main()
{
	{
		auto obj = func1();
		std::cout << obj.a << std::endl; // bad
	}
	std::cout << "================" << std::endl;
	{
		auto obj = func2();
		std::cout << obj.a << std::endl; // good
	}
}
