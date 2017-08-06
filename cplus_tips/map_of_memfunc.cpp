/**
 * call member func via map
 */
#include <map>
#include <functional>
#include <string>
#include <iostream>

class A {

	int f(int a) {
		std::cout << a << std::endl;
	}

	std::map<std::string, decltype(&A::f)> mymap = { { "abc", &A::f }};

	public:
	void call()
	{
		auto memfunc = std::bind(mymap["abc"], this, std::placeholders::_1);
		memfunc(3);
	}
};


int main()
{
	A a;
	a.call();
}
