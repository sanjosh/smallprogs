#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <atomic>
#include <future>
#include <cstdint>

std::atomic<int64_t> a{0};
int numThreads = 2;
int loops = 1000000;

void BindThreadToCore(int cpu_id) {
  cpu_set_t cs; 
  CPU_ZERO(&cs);
  CPU_SET(cpu_id, &cs);
  auto r = pthread_setaffinity_np(pthread_self(), sizeof(cs), &cs);
  if (r != 0) {
    std::cerr << "failed thread bind=" << cpu_id << std::endl;
  }
}


void func(int64_t oldval) {
    BindThreadToCore(oldval);
    //std::ostringstream ss;
    do {
        bool worked = std::atomic_compare_exchange_strong(&a, &oldval, oldval + numThreads);
        //ss << oldval << "," << std::this_thread::get_id() << std::endl;
        oldval += numThreads;
    }  while (oldval < numThreads * loops);
    //std::cout << ss.str();
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        numThreads = atoi(argv[1]);
    }

    std::vector<std::future<void>> futVec;

    for (int i = 0; i < numThreads; i++) {
        auto f1 = std::async(std::launch::async, func, i);
        futVec.emplace_back(std::move(f1));
    }

    for (auto &fut : futVec) {
        fut.wait();
    }
}
