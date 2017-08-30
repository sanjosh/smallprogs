#include <vector>
#include <iostream>
#include <cassert>
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

int quickselect(std::vector<int>& a, int left, int right, int rank_required) {
	if (left < right) {
		int p = partition(a, left, right);
		if (rank_required < p) {
			// elem falls on left since rank is less than length of left
			return quickselect(a, left, p - 1, rank_required);
		} else if (rank_required > p) { 
			// elem falls on right since rank is greater than length of left side
			// decrement the rank to send relative rank to subroutine
			return quickselect(a, p + 1, right, rank_required - p);
		} else {
			return p;
		}
	} else if (left == right) {
		return left;
	} else {
		assert(0);
	}
}

void find_rank(std::vector<int> a, int rank) {
	int k = quickselect(a, 0, a.size() - 1, rank);
	std::for_each(a.begin(), a.end(), [] (int elem) { 
		std::cout << elem << ",";
	});
	std::cout << std::endl;
	std::cout << "rank=" << rank << " is " << a[k] << std::endl;
	std::cout << "-----------------" << std::endl;
}

int main() {
	find_rank({ 1, 5, 2, 5, 7, 3, 9, 11}, 0);
	find_rank({ 1, 5, 2, 5, 7, 3, 9, 11}, 1);
	find_rank({ 1, 5, 2, 5, 7, 3, 9, 11}, 2);
	find_rank({ 1, 5, 2, 5, 7, 3, 9, 11}, 3);
	find_rank({ 1, 5, 2, 5, 7, 3, 9, 11}, 7);
	find_rank({1}, 0);
	find_rank({2, 1}, 0);
	find_rank({2, 1}, 1);
	find_rank({3, 2, 1}, 2); 
}

