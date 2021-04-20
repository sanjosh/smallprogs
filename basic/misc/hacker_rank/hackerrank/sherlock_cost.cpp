/**
 * sherlock and cost
 * https://www.hackerrank.com/challenges/sherlock-and-cost
 */
#include <iostream>
#include <vector>
#include <list>

typedef std::vector<int> VecNum;

void get_sum(VecNum& max_arr, int idx, int& min_sum, int& max_sum) {

	int n = max_arr.size();

	if (idx == (n -1)) {
		return;
	}
	if (idx < (n - 2)) {
		get_sum(max_arr, idx + 1, min_sum, max_sum);
	}
	// max[n] - max[n + 1]
	int max_sum2 = abs(max_arr[idx] - max_arr[idx + 1]) + max_sum;
	// max[n] - min[n + 1]
	int max_sum1 = abs(max_arr[idx] - 1) + min_sum;

	// min[n] - min[n + 1]
	int min_sum1 = abs(1 - 1) + min_sum;
	int min_sum2 = abs(1 - max_arr[idx + 1]) + max_sum;
	// max[n] - min[n + 1]
	// min[n] - max[n + 1]
	max_sum = std::max(max_sum1, max_sum2);
	min_sum = std::max(min_sum1, min_sum2);

	//std::cout << idx << ":" << min_sum << "," << max_sum << std::endl;
}

int main() {

	int num_test_cases = 0;
	scanf("%d", &num_test_cases);

	std::list<VecNum> tests;

	for (int t = 0; t < num_test_cases; t++) {
		int num_entries;
		scanf("%d", &num_entries);
		VecNum vec(num_entries);
		for (int i = 0; i < num_entries; i ++) {
			scanf("%d", &vec[i]);
		}
		tests.emplace_back(std::move(vec));
 	}

	for (auto &iter : tests) {
		int min_sum = 0;
		int max_sum = 0;
		get_sum(iter, 0, min_sum, max_sum);
		std::cout << std::max(min_sum, max_sum) << std::endl;
	}
}

