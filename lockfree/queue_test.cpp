#include <thread>
#include <vector>
#include <mutex>
#include <cassert>
#include <iostream>

#include "queue.h"

Queue q;

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

void popFunc() {
	std::vector<int64_t> valvec;
	int64_t val;
	for (int i = 0; i < TOTALVAL/TOTALTHR; i++) {
		val = q.dequeue();
		if (val != -1) {
			valvec.push_back(val);
		} else {
			//std::cout << "queue empy" << std::endl;
		}
	}
	m.lock();
	kValVec.insert(kValVec.end(), valvec.begin(), valvec.end());
	m.unlock();
}

void pushFunc(int offset) {
	for (int i = 0; i < TOTALVAL/TOTALTHR; i++) {
		q.enqueue(offset + (i * TOTALTHR));
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
		popThr.emplace_back(popFunc);
		pushThr.emplace_back(pushFunc, i + 1);
	}

	for (auto& th : pushThr) th.join();
	for (auto& th : popThr) th.join();

	//assert(q.size() == 0);

	Modulo<10> i;
	for (auto v  : kValVec) {
		std::cout << v << ",";
		if (i.rollover()) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
