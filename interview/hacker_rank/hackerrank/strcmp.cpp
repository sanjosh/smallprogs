#include <bits/stdc++.h>

/**
	https://www.hackerrank.com/challenges/big-sorting/forum
 */

using namespace std;

struct less_than 
{
	inline bool operator () (const string& a, const string& b) 
	{
		if (a.size() > b.size()) {
			return false;
		} else if (a.size() < b.size()) {
			return true;
		}
		for (int i = 0; i < a.size(); i ++) {
			if (a[i] != b[i]) {
				if (a[i] > b[i]) {
					return false;
				} else {
					return true;
				}
			}
		}
		//https://stackoverflow.com/questions/18291620/why-will-stdsort-crash-if-the-comparison-function-is-not-as-operator?lq=1
		// weak ordering rule - if equal, do not return a < b
		return false;
	}
};

int main(){
    int n;
    cin >> n;
    vector<string> unsorted(n);
    for(int unsorted_i = 0; unsorted_i < n; unsorted_i++){
       cin >> unsorted[unsorted_i];
    }

		std::sort(unsorted.begin(), unsorted.end(), less_than());
		//std::sort(unsorted.begin(), unsorted.end());
		for (auto elem : unsorted) {
			cout << elem << endl;
		}
    return 0;
}

