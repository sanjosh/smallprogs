/**
 * can array be divided into partition of equal sum 
 * dynamic programming
 */
#include <vector>
#include <iostream>
#include <cstdint>

using namespace std;

bool isequal(const std::vector<int32_t>& array, 
	int index, 
	vector<int32_t>& a, 
	vector<int32_t>& b)
{
	if (index == array.size()) {
		int32_t leftsum = 0;
		for (int32_t i : a) {
			leftsum += i;
		}
		int32_t rightsum = 0;
		for (int32_t i : b) {
			rightsum += i;
		}
		if (rightsum == leftsum) {
			std::cout << rightsum << std::endl;
		}
		return rightsum == leftsum;
	} else if (index == 0) {
		a.push_back(array[index]);
		return isequal(array, index + 1, a, b);
	} else {
		vector<int32_t> ac = a;
		ac.push_back(array[index]);
		const bool left = isequal(array, index + 1, ac, b);
		vector<int32_t> bc = b;
		bc.push_back(array[index]);
		const bool right = isequal(array, index + 1, a, bc);
		return left | right;
	}
}

int main()
{
	vector<int32_t> ar = {3, 1, 4, 7, 8, 3};
	vector<int32_t> a;
	vector<int32_t> b;
	bool res = isequal(ar, 0, a, b);
	std::cout << res << std::endl;

}
