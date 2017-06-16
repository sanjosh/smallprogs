#include <thread>
#include <vector>
#include <unistd.h>
#include <mutex>
#include <cassert>
#include <iostream>

#include "spsc_queue.h"

SPSCQueue q;

int TOTALVAL = 500;

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

void popFunc() {
	std::vector<int64_t> valvec;
	for (int i = 0; i < TOTALVAL; i++) {
		bool is_empty;
		int64_t val;
		do {
			val = q.dequeue(is_empty);
		} while (is_empty);
		assert(val < TOTALVAL);
		valvec.push_back(val);
	}
	kValVec.insert(kValVec.end(), valvec.begin(), valvec.end());
}

void pushFunc() {
	std::vector<int64_t> valvec;
	for (int i = 0; i < TOTALVAL; i++) {
		int64_t val = i;
		valvec.push_back(val);
		q.enqueue(val);
		if (i && (i % 10 == 0)) sched_yield();
	}
}

int main(int argc, char* argv[])
{
	if (argc == 2) {
		TOTALVAL = atoi(argv[1]);
	}
	std::vector<std::thread> popThr;
	std::vector<std::thread> pushThr;

	popThr.emplace_back(popFunc);
	pushThr.emplace_back(pushFunc);

	for (auto& th : pushThr) th.join();
	for (auto& th : popThr) th.join();

	assert(q.size() == 0);

	Modulo<10> i;
	for (auto v  : kValVec) {
		std::cout << v << ",";
		if (i.rollover()) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
