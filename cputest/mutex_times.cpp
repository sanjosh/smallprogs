#include <mutex>
#include <iostream>
#include <atomic>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

size_t max = 0;

uint64_t wm_ctr = 0;
std::mutex m;

void with_mutex() {
	for (size_t idx = 0; idx < max; idx ++) {
		m.lock();
		wm_ctr ++;
		m.unlock();
	}
}

uint64_t nm_ctr = 0;
void no_mutex() {
	for (size_t idx = 0; idx < max; idx ++) {
		nm_ctr ++;
	}
}

std::atomic<uint64_t> a_ctr{0};
void atomic_ctr() {
	for (size_t idx = 0; idx < max; idx ++) {
		a_ctr ++;
	}
}

template <typename Func>
void do_count(std::string name, Func&& f) {
	Clock::time_point begin = Clock::now();
	f();
	Clock::time_point end = Clock::now();

	std::cout 
		<< name << ":" 
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
		<< std::endl;
}

int main(int argc, char* argv[]) {
	max = atoll(argv[1]);

	do_count("with mutex", with_mutex);
	do_count("atomic ctr", atomic_ctr);
	do_count("no mutex", no_mutex);
}
