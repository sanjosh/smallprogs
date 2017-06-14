#include <thread>
#include <vector>
#include <mutex>
#include <cassert>
#include <iostream>

#include "set.h"

Set s;

int TOTALVAL = 500;
int TOTALTHR = 5;

std::mutex m;
std::vector<int64_t> kValVec;

template <int k>
struct Modulo {
	int i = 0;
	bool rollover() {
		++i;
		if (i == k) {
			i = 0;
			return true;
		}
		return false;
	}
};

void popFunc(int offset) {
	std::vector<int64_t> valvec;
	for (int i = 0; i < TOTALVAL/TOTALTHR; i++) {
		int64_t val = offset + (i * TOTALTHR);
		bool ret = s.remove(val);
		assert(ret == true);
		valvec.push_back(val);
	}
	m.lock();
	kValVec.insert(kValVec.end(), valvec.begin(), valvec.end());
	m.unlock();
}

void pushFunc(int offset) {
	for (int i = 0; i < TOTALVAL/TOTALTHR; i++) {
		s.insert(offset + (i * TOTALTHR));
	}
}

int main(int argc, char* argv[])
{
	if (argc == 3) {
		TOTALTHR = atoi(argv[1]);
		TOTALVAL = atoi(argv[2]);
	}
	std::vector<std::thread> popThr;
	std::vector<std::thread> pushThr;

	for (int i = 0; i < TOTALTHR; ++i ) {
		pushThr.emplace_back(pushFunc, i + 1);
	}
	for (auto& th : pushThr) th.join();

	for (int i = 0; i < TOTALTHR; ++i ) {
		popThr.emplace_back(popFunc, i + 1);
	}
	for (auto& th : popThr) th.join();

	Modulo<10> i;
	for (auto v  : kValVec) {
		std::cout << v << ",";
		if (i.rollover()) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
