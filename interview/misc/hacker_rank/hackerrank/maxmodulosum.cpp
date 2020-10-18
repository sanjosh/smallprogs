/*
 Print largest contiguous array sum modulo some number

	Given an -element array of integers, and an integer, determine the maximum 
    value of the sum of any of its subarrays modulo 

 https://www.hackerrank.com/challenges/maximum-subarray-sum

 */

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <climits>
#include <limits>

using namespace std;

typedef std::vector<uint64_t> VecNum;
 
uint64_t maxSubArraySum(const VecNum& a, uint64_t Modulo)
{
  uint64_t max_so_far = std::numeric_limits<uint64_t>::min();
	uint64_t max_ending_here = 0;
	uint64_t prev_ending_here = 0;
	size_t size = a.size();
 
	for (size_t i = 0; i < size; i++)
	{
		max_ending_here = (max_ending_here + a[i]) % Modulo;
		if (i > 0) { prev_ending_here = (prev_ending_here + a[i]) % Modulo; 
	}

	if (max_ending_here == 0) {
		max_ending_here = prev_ending_here;
		prev_ending_here = a[i] % Modulo;
	}

	if (max_so_far < max_ending_here)
		max_so_far = max_ending_here;

	if (max_so_far < prev_ending_here)
		max_so_far = prev_ending_here;

	if (max_ending_here < 0)
		max_ending_here = 0;

	}
	return max_so_far;
}
 
int main(int argc, char* argv[])
{
	int num_test_cases = 0;
  scanf("%d", &num_test_cases);

  std::vector<VecNum> tests;
  std::vector<uint64_t> mods;

  for (int t = 0; t < num_test_cases; t++) {
		int n = 0;
	  uint64_t d = 0;
	  scanf("%d %lu", &n, &d);
		VecNum arr(n);
	  for (int i = 0; i < n; i++)
	  {
	    scanf("%lu", &arr[i]);
	  }
		mods.push_back(d);
		tests.emplace_back(arr);
	}

	for (int i = 0; i < tests.size(); i ++) {
		const auto& vec = tests[i];
		auto max_sum = maxSubArraySum(vec, mods[i]);
		cout << max_sum << std::endl;
	}
  return 0;
}
