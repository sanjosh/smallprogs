#include <iostream>
#include <string.h>

/**
 * rabbits multiplying into 2 every day and dying after k days
 */

int dying_after = 5;

int64_t bottom(int n) {

	int64_t* f = new int64_t[n + 1];

	f[0] = 1;

	for (int i = 1 ; i <= n; i++) {
		f[i] = (3 * f[i - 1]);
		if (i >= dying_after) {
			f[i] -= f[i - dying_after];
		}
	}

	int64_t r = f[n];
	delete [] f;
	return r;
}

int64_t topdown(int n) {
	if (n == 0) {
		return 1;
	}
	return (topdown(n-1) * 3) - ((n >= dying_after) ? topdown(n-dying_after) : 0);
}

static int64_t* memof = nullptr;

int64_t topdown_memo(int n) {

	if (n == 0) {
		memof[n] = 1;
	} else if (memof[n] == -1) {
		memof[n] = (topdown(n-1) * 3) - ((n >= dying_after) ? topdown(n-dying_after) : 0);
	}
	return memof[n];
}

int main(int argc, char* argv[]) {

	constexpr int kMaxDays = 100;
	memof = new int64_t[kMaxDays];
	for (int i = 1; i < kMaxDays; i ++) {

		for (int j = 0; j < i + 1; j++) {
			memof[j] = -1;
		}

		int64_t b = bottom(i);
		int64_t t = topdown_memo(i);
		if (b != t) {
			std::cerr << i << ":" << b << "," << t << std::endl;
		} else {
			std::cout << i << "," << b << std::endl;
		}
		//if (i && i % 10 == 0) { 
			//std::cout << i << std::endl;
		//}

	}
	delete []memof;
}
