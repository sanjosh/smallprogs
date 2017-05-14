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

using namespace std;

int Modulo = 7;
 
int maxSubArraySum(int a[], int size)
{
    int max_so_far = INT_MIN, max_ending_here = 0;
	int prev_ending_here = 0;
 
    for (int i = 0; i < size; i++)
    {
        max_ending_here = (max_ending_here + a[i]) % Modulo;
        if (i > 0) { prev_ending_here = (prev_ending_here + a[i]) % Modulo; }

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

		//std::cout << max_so_far << "," << max_ending_here << "," << prev_ending_here << "," << a[i] << endl;
    }
    return max_so_far;
}
 
int main(int argc, char* argv[])
{
	Modulo = 7;
	if (argc == 2) { Modulo = atoi(argv[1]); }

	std::list<std::vector<int>> listvec;
	listvec.emplace_back(std::vector<int>({2, 2, 3, 2, 2, 3}));
	listvec.emplace_back(std::vector<int>({2, 2, 3}));
	listvec.emplace_back(std::vector<int>({9, 9, 3, 3, 5}));
	listvec.emplace_back(std::vector<int>({6, 6, 6, 6, 6, 6, 6, 6}));
	listvec.emplace_back(std::vector<int>({3, 4, 3, 4, 3, 4, 3, 4}));
	listvec.emplace_back(std::vector<int>({7}));
	listvec.emplace_back(std::vector<int>({1, 1, 1, 4, 1, 1, 1, 4, 1, 1, 1}));
	listvec.emplace_back(std::vector<int>({1, 2, 4, 2, 1, 2, 4, 2, 1, 1}));
	listvec.emplace_back(std::vector<int>({2, 2, 0, 2, 2, 0}));

	for (auto& vec : listvec) {
		int max_sum = maxSubArraySum(&vec[0], vec.size());
		for (auto elem : vec) {
			cout << elem << ",";
		}
		cout << ":sum=" << max_sum << std::endl;
	}
    return 0;
}
