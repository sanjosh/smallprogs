// g++ -O3 -std=c++14 -lpthread
#include <atomic>
#include <thread>
#include <cassert>
#include <future>
#include <iostream>
#include <vector>
#include <cstdint>

#include <sched.h> // sched_getscheduler

void BindThreadToCore(int cpu_id)
{
    cpu_set_t cs; 
    CPU_ZERO(&cs);
    CPU_SET(cpu_id, &cs);
    auto r = pthread_setaffinity_np(pthread_self(), sizeof(cs), &cs);
    assert(r == 0); 
}

std::atomic<uint64_t> ctr{0};
int num_threads = 2;
const uint64_t till = 1000000000ULL;
bool strict = false;

/** 
 * using sequential consistency
 */
uint64_t strict_cond_compare(uint64_t newval) {
	uint64_t curval = 0;
	do {
		curval = ctr.load();
		if (curval >= newval) { return curval; }
	} while (!ctr.compare_exchange_strong(curval, newval));
	return newval;
}

/** 
 * using weaker consistency
 */
uint64_t loose_cond_compare(uint64_t newval) {
	uint64_t curval = 0;
	do {
		curval = ctr.load(std::memory_order_relaxed);
		if (curval >= newval) { return curval; }
	} while (!ctr.compare_exchange_weak(curval, newval, 
		std::memory_order_release, 
		std::memory_order_relaxed));
	return newval;
}


uint64_t thrfunc(bool strict, uint64_t start)
{
	BindThreadToCore(start - 1);
	uint64_t num_iter = 0;
	uint64_t next = start;
	uint64_t retval = 0;
	do {
		if (strict) {
			retval = strict_cond_compare(next);
		} else {
			retval = loose_cond_compare(next);
		}
		next += num_threads;
		num_iter ++;
	} while (retval < till);
	return num_iter;
}

void do_oneround() {

	std::vector<std::future<uint64_t>> futvec;
	for (int i = 0; i < num_threads; i++)
	{
		auto f = std::async(std::launch::async, thrfunc, strict, i + 1);
		futvec.emplace_back(std::move(f));
	}

	for (auto& fut : futvec) {
		uint64_t ret = fut.get();
		std::cout << ret << std::endl;
	}
	std::cout << ctr << std::endl;
	std::cout << "--------------" << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc > 1) {
		strict = true;
	}
	// do as many rounds as many as number of cpus
	for (int i = 2; i < 5; i++) {
		ctr.store(0);
		num_threads = i;
		do_oneround();
	}
}
