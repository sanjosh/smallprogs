#include <vector>
#include <cassert>
#include <iostream>

// 0 111 22 33 44

using namespace std;

void counting_sort(std::vector<int> &a, 
		std::vector<int> &b, 
		int k) {

	std::vector<int> c(k, 0);

	for (int j = 0; j < a.size(); j++) {
		c[a[j]] ++; // PDF
	}

	for (int i = 1; i < k; i++) {
		c[i] = c[i] + c[i-1]; // CDF
	}

	for (int j = a.size() - 1; j >= 0; j--) {
		int idx = c[a[j]] - 1;
		//cout << "b[" << idx << "]=" << a[j] << endl;
		assert(b[idx] == 0);
		b[idx] = a[j];
		c[a[j]] --;
	}
	for (int i = 0; i < k; i++) {
		cout << c[i] << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[]) {

	int n;
	cin >> n;
	int k;
	cin >> k;
	std::vector<int> a(n);
	std::vector<int> b(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];	
		assert(a[i] < k);
	}
	counting_sort(a, b, k);
	for (auto elem : b ) {
		cout << elem << " ";
	}
	cout << endl;
	
}
