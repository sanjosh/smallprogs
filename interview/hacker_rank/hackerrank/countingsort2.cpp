
#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	long n;
	cin >> n;
	std::map<int, int> freq;
	for (int i = 0; i < 100; i ++) {
		freq.insert({i, 0});
	}
	for (int i = 0; i < n; i ++) {
		int a;
		cin >> a;
		auto iter = freq.lower_bound(a);
		if (iter != freq.end() && !(freq.key_comp()(a, iter->first))) {
			iter->second ++;
		} else {
			assert(0);
		}
	}
	assert(freq.size() == 100);
	for (auto elem : freq) {
		for (int j = 0; j < elem.second; j ++) {
			cout << elem.first << " ";
		}
	}
	cout << endl;
	return 0;
}

