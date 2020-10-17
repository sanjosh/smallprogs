#include <vector>
#include <iostream>
#include <algorithm>

void swap(std::vector<int>& a, int p1, int p2) {
	if (p1 != p2) {
		std::cout << "swap " << p1 << "," << p2 << std::endl;
		int x = a[p1];
		a[p1] = a[p2];
		a[p2] = x;
	}
}

int partition(std::vector<int>& a, int left, int right) {
	std::cout << "partition " << left << "," << right << std::endl;
	int low_idx = left - 1;
	// pick last elem as pivot
	int pivot = a[right];

	for (int idx = left; idx < right; idx ++) {
		// any elem less than pivot must move to left side
		if (a[idx] <= pivot) {
			low_idx ++;
			swap(a, low_idx, idx);
		}
	}
	// move pivot to center
	swap(a, low_idx + 1, right);
	// return pivot index
	return low_idx + 1;
}

void quicksort(std::vector<int>& a, int l, int h) {
	if (l < h) {
		int p = partition(a, l, h);
		quicksort(a, l, p - 1);
		quicksort(a, p + 1, h);
	}
}

void do_sort(std::vector<int> a) {
	quicksort(a, 0, a.size() - 1);
	std::for_each(a.begin(), a.end(), [] (int elem) { 
		std::cout << elem << ",";
	});
	std::cout << std::endl;
	std::cout << "-----------------" << std::endl;
}

int main() {
	do_sort({ 1, 5, 2, 5, 7, 3, 9, 11});
	do_sort({1});
	do_sort({2, 1});
	do_sort({3, 2, 1});
}

