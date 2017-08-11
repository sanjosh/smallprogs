/**
 * lazy generation of range or lazy iteration over container 
 */
#include <iostream>
#include <set>
#include <functional>

int main()
{
	auto generator = []() {  
		int i = 0;  
		return [=]() mutable {    
			return i < 10 ? i++ : -1;  
		};
	}();

	int ret = 0; 
	while ((ret = generator()) != -1) {
		std::cout << "generator: " << ret << std::endl;
	}

	std::set<int> sett{1, 2, 3, 4, 5, 6 };
	std::set<int>::iterator iter = sett.begin();

	auto genset = [&] () {
		return [&]() mutable {    
			bool not_iterend = (iter != sett.end());
			int val = (not_iterend) ? *iter : -1;
			++ iter;
			return val;
		};
	}();

	while ((ret = genset()) != -1) {
		std::cout << "genset: " << ret << std::endl;
	}
}
