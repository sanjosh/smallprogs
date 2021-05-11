#include <iostream>
#include <set>

/*
 * generate combinations C(n, r)

 * same as path between diagonals in a square matrix (0 indicating go right, 1 indicating go up)
 https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/

 C(n, r) = C(n-1, r) + C(n-1, r-1)

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
