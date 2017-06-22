#include <cstdint>
#include <chrono>
#include <iostream>

/*
 * iterate by row or column - cpu cache test
 */

int num_rows = 0;
int num_cols = 0;
int64_t *array = nullptr;

typedef std::chrono::high_resolution_clock Clock;

void byrow()
{
	for (int r = 0; r < num_rows; r ++) {
		for (int c = 0; c < num_cols; c ++) {
			array[(r * num_cols) + c] = 3;
		}
	}
}

void bycol()
{
	for (int c = 0; c < num_cols; c ++) {
		for (int r = 0; r < num_rows; r ++) {
			array[(r * num_cols) + c] = 4;
		}
	}
}

template <class Lambda>
int64_t measureMe(Lambda&& func) {
	Clock::time_point s = Clock::now();
	func();
	Clock::time_point t = Clock::now();
	const int64_t diff = std::chrono::duration_cast<std::chrono::nanoseconds>(t - s).count();
	return diff;
}


int measure()
{
	array = new int64_t[num_rows * num_cols];
	std::cout << num_rows << "," << num_cols << "," << measureMe(byrow) << "," << measureMe(bycol) << std::endl;
	delete array;
}

int main() {
	int max_rows = 65536;
	int max_cols = 65536;
	std::cout << "rows,cols,byrow,bycol" << std::endl;
	for (int r = 512; r < max_rows; r = r << 1)
	for (int c = 512; c < max_cols; c = c << 1)
	{
		num_rows = r;
		num_cols = c;
		measure();
	}

}
