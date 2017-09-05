#include <iostream>
#include <set>

/*
 * generate combinations C(n, r)
 */

int n = 5;
int r = 3;
int arr[] = {1, 2, 3, 4, 5};

typedef std::set<int> Set;
using namespace std;

void print_set(const Set& s) {
		for (auto elem : s) {
			cout << elem << " ";
		}
		cout << std::endl;
}

void recur(Set s, int idx) {

	if (s.size() == r) {
		return print_set(s);
	}

	for (int i = idx; i <= n - r + idx && i < n; i ++) {
		Set newset(s);
		newset.insert(arr[i]);
		recur(newset, i + 1);
	}
}

int main()
{
	Set s;
	recur(s, 0);
}
