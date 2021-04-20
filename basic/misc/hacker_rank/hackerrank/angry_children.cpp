
/*
https://www.hackerrank.com/challenges/angry-children-2
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cassert>
using namespace std;

std::priority_queue<long> q; // largest at top

void solve(long arr[], int N, int K) {

	std::sort(arr, arr + N);

  for (int i = 0; i < K-1; i++) {
		q.push(arr[i+1] - arr[i]);
		std::cout << arr[i+1] << "," << arr[i] << std::endl;
	}
	assert(q.size() == K-1);

  for (int i = K - 1; i < N-1; i ++) {
		long diff = arr[i+1] - arr[i];
		if (diff < q.top()) {
			std::cout << arr[i+1] << "," << arr[i] << std::endl;
			q.pop();
			q.push(diff);	
		}
	} 

	assert(q.size() == K-1);
	long min_diff = 0; 

		std::vector<int> vec;
		assert(q.size() == K-1);
		for (int i = 0; i < K-1; i ++) {
			auto elem = q.top();	
			std::cout << "diff=" << elem << std::endl;
			min_diff += elem;
			vec.push_back(elem);
			q.pop();
		}

	int incr = 1;
	do {

		std::cout << min_diff << " incr=" << incr << std::endl;

		for (int i = 0; i < vec.size() - incr; i++) {
			long subsum = 0;
			// sum of incr subsets of vec
			for (int j = i; j <= i + incr; j ++) {
				subsum += vec[j];
			}
			min_diff += subsum;
		}
		incr ++;

	} while (incr < vec.size());

	std::cout << min_diff << std::endl;
}

int main() {
    int N, K;
     cin >> N >> K;
    long arr[N];
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    solve(arr, N, K);
    return 0;
}
