#include <iostream>
#include <string>

/**
 * complexity O(mn) bcos binary tree
 */

int lcs(const std::string& a, const size_t an, 
	const std::string& b, const size_t bn)
{
	int L[an + 1][bn + 1];

	for (int i = 0; i <= an; i++) 
	{
		for (int j = 0; j <= bn; j++)
		{
			if (i == 0 || j == 0) {
				L[i][j] = 0;
			} else if (a[i-1] == b[j-1]) {
				L[i][j] = L[i-1][j-1] + 1;
			} else {
				L[i][j] = std::max(L[i-1][j], L[i][j-1]);
			}
		}
	}
	return L[an][bn];
}


int main(int argc, char* argv[]) {
	std::string a = argv[1];
	std::string b = argv[2];

	std::cout << "lcs=" << lcs(a, a.size(), b, b.size()) << std::endl;
}
