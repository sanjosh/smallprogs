#include <iostream>
#include <string>

/**
 * complexity O(2^n) bcos binary tree
 */

int lcs(const std::string& a, const size_t an, 
	const std::string& b, const size_t bn)
{
	//std::cout << an << "," << bn << std::endl;
	if ((an == 0) || (bn == 0)) {
		return 0;
	}
	if (a[an-1] == b[bn-1]) {
		return lcs(a, an-1, b, bn-1) + 1;
	} else {
		const int left = lcs(a, an-1, b, bn);
		const int right = lcs(a, an, b, bn-1);
		return std::max(left, right);
	}
}


int main(int argc, char* argv[]) {
	std::string a = argv[1];
	std::string b = argv[2];

	std::cout << "lcs=" << lcs(a, a.size(), b, b.size()) << std::endl;
}
