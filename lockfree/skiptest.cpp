/*
 * g++ <file>.cpp -std=c++14 -I/usr/local/include -lfolly -lglog -lpthread
 */

#include <folly/ConcurrentSkipList.h>
#include <set>
#include <cstdint>

typedef std::pair<int64_t, int64_t> interval_t;
typedef std::set<int64_t> batchset_t;
typedef std::pair<interval_t, batchset_t> iv_t;

struct IVLessThan {
	bool operator() (const iv_t& left, const iv_t& right) {
		return left.first.first < right.first.first;
	}
};

typedef folly::ConcurrentSkipList<iv_t, IVLessThan> ivmap_t;

int main() {

	ivmap_t t(24);

	{
		ivmap_t::Accessor writer(&t);
		for (int64_t i = 0; i < 100; i++) {
			interval_t ivl = std::make_pair(i, i+10);
			batchset_t bs;
			int64_t j = i;
			std::generate_n(std::inserter(bs, bs.begin()), 10, [&j](){return j++;});
			writer.insert(std::make_pair(ivl, bs));
		}
	}

	{
		ivmap_t::Accessor reader(&t);
		iv_t lb;
		lb.first.first = 50;
		for (auto iter = reader.find(lb); iter != reader.end(); ++iter) {
			auto elem = *iter;
			std::cout << elem.first.first << "," << elem.first.second << std::endl;
			for (auto& set_elem : elem.second) {
				std::cout << set_elem;
			}
			std::cout << std::endl;
		}
	}

	{
		ivmap_t::Accessor reader(&t);
		ivmap_t::Skipper skipper(reader);
		iv_t lb;
		lb.first.first = 50;
		skipper.to(lb);
		while (skipper.good()) {
			auto elem = skipper.data();
			std::cout << elem.first.first << "," << elem.first.second << std::endl;
			for (auto& set_elem : elem.second) {
				std::cout << set_elem;
			}
			std::cout << std::endl;
			++ skipper;
		}
	}
}
