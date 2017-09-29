#include <re2/re2.h>
#include <string>
#include <iostream>

int main()
{
	int num = 0;
	std::string s;
	while (std::cin >> s) {
		const bool got = RE2::PartialMatch(s, "sk.*ng");
		if (got) num ++; 
	}
	if (num) std::cout << num << std::endl;
}
