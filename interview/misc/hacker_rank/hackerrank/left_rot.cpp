/*
	https://www.hackerrank.com/challenges/array-left-rotation
 */
#include <iostream>
#include <vector>
#include <algorithm>

void arr_print(const std::vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void left_rotate(std::vector<int>& arr, const size_t d) {

	int n = arr.size();
	if (n == d) return;

	int num_moved = 0;
	int start_off = 0;

	// as long as all elements not touched
	while (num_moved < n) {
		// save first element of cycle
		const int tmp = arr[start_off];
		int i = start_off;
		do {
			const int next = (i + d) % n;
			arr[i] = arr[next];
			num_moved ++;
			if (next == start_off) {
				// break if reached beginning of cycle
				break;
			}
			i = next;
		} while (1);
		// set last elem of cycle
		arr[i] = tmp;
		// move to next offset in array
		start_off ++;
	}
}

int main(int argc, char* argv[]) {
	int n = 0;
	int d = 0;
	scanf("%d %d", &n, &d);
	std::vector<int> arr(n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
  }
	left_rotate(arr, d);
	arr_print(arr);
}
