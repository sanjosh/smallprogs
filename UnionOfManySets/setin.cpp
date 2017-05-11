#include <boost/container/flat_set.hpp>
#include <list>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <queue>
#include <chrono>
#include <iostream>
#include <random>

/**
 * Compare 2 ways to do union of N sets
 * (a) using min heap of N iterators (one for each set) 
 * (b) do union of 2 sets at a time over N sets
 *
 * If maxBatchId is small, (b) is faster
 * If maxBatchId is large, (a) is faster
 */

typedef boost::container::flat_set<int64_t> IntSet;
typedef IntSet::const_iterator IntSetIter;
typedef std::chrono::high_resolution_clock ClockMe;

struct SetIter {
	IntSetIter iter;
	IntSet c;

	SetIter(const IntSet& ci) {
		c = ci;
		iter = c.begin();
	}
};

struct SetComparator
{
	static int64_t numcmp; // number of times comparator invoked
	public:
	bool operator () (const SetIter* lhs, const SetIter* rhs) const {
		numcmp ++;
		return *(lhs->iter) > *(rhs->iter);
	}
};

int64_t SetComparator::numcmp = 0;

typedef std::list<SetIter*> ListSetIter;
typedef std::list<IntSet> ListIntSet;
typedef std::priority_queue<SetIter*, std::vector<SetIter*>, SetComparator> MinHeapOfSets;

/** 
 * find union of many sets using min heap/priority queue
 */
IntSet UnionUsingMinHeap(ListSetIter& s) {
	MinHeapOfSets ps;
	for (auto siter : s) {
		ps.push(siter);
	}
	SetComparator::numcmp = 0;

	IntSet result;
	int64_t last_val = -1;
	while (!ps.empty()) {
		auto siter = ps.top();
		int64_t cur_val = *(siter->iter);
		if (last_val != cur_val) {
			result.insert(cur_val);
			last_val = cur_val;
		}
		ps.pop();
		++ siter->iter;
		if (siter->iter != siter->c.end()) {
			ps.push(siter);
		}
	}
	return result;
}

/** 
 * find union of many sets by taking union of two sets at a time
 */
IntSet UnionOfSetByPairs(ListIntSet& s) {

	auto siter = s.cbegin();
	IntSet result = *siter;
	++ siter;

	while (siter != s.end()) {
		const IntSet& curset = (*siter);
		IntSet temp;
		// union into temporary set
		std::set_union(result.begin(), result.end(),
			curset.begin(), curset.end(),
			std::inserter(temp, temp.begin()));
		// move temp set to result again
		result = std::move(temp);
		++ siter;
	}
	return result;
}


/**
 * @param NumSets number of sets 
 * @param minElemPerSet min number of elems to put in each set
 * @param maxElemPerSet max number of elems to put in each set
 * @param maxBatchId range of elem in each set is between [0, maxBatchId]
 */
void OneLoop(int NumSets, int minElemPerSet, int maxElemPerSet, int64_t maxBatchId) {

	std::mt19937 seedGen(getpid());
	std::uniform_int_distribution<int64_t> numElemsInSetGen(minElemPerSet, maxElemPerSet);
	std::uniform_int_distribution<int64_t> batchIdGen(0, maxBatchId);

	ListIntSet ls;
	// for each set, generate between [minElemPerSet, maxElemPerSet] random elements which are less than [maxBatchId]
	for (int i = 0; i < NumSets; i++) {
		IntSet s;
		std::generate_n(std::inserter(s, s.begin()), numElemsInSetGen(seedGen), [&]() {return batchIdGen(seedGen); });
		ls.emplace_back(s);
	}
	IntSet res1;
	IntSet res2;

	int64_t setunion_us = 0;
	int64_t priosort_us = 0;
	{
		ClockMe::time_point begin = ClockMe::now();
		res1 = UnionOfSetByPairs(ls);
		ClockMe::time_point end = ClockMe::now();
		setunion_us = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

	}
	{
		ListSetIter li;
		for (auto& aset : ls) {
			li.emplace_back(new SetIter(aset));
		}
		ClockMe::time_point begin = ClockMe::now();
		res2 = UnionUsingMinHeap(li); 
		ClockMe::time_point end = ClockMe::now();
		priosort_us = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	}

	IntSet union_set;
	IntSet inter_set;
	std::set_union(res1.begin(), res1.end(),
			res2.begin(), res2.end(),
			std::inserter(union_set, union_set.begin()));
	std::set_union(res1.begin(), res1.end(),
			res2.begin(), res2.end(),
			std::inserter(inter_set, inter_set.begin()));

	// verify both results are same and their union & intersect is same 
	assert(union_set.size() == inter_set.size());
	assert(union_set.size() == res1.size());
	assert(union_set.size() == res2.size());

	// speedup factor
	const float factor = (float)setunion_us / (float)priosort_us;
	const char ch = (factor > 1.0) ? 'Y' : 'N';
	std::cout << NumSets << "," << minElemPerSet << "," << maxElemPerSet  << "," << maxBatchId
	   << "," << setunion_us << "," << priosort_us << "," << factor << "," << ch 
	   << "," << SetComparator::numcmp << "," << res1.size() 
	   << std::endl;
}

int main(int argc, char* argv[])
{
	int minElemPerSet = 200;

	std::cout << "numsets,minelems,maxelems,maxbatchid,setunion(us),minheap(us),speedup,numheapcmp,result_size" << std::endl;
	for (int64_t maxBatchId = (1 << 16); maxBatchId < (1 << 30); maxBatchId = maxBatchId << 1) {
		for (int numSets = 16; numSets < 16384; numSets *= 2) {
			for (int maxElemPerSet = 500; maxElemPerSet < 15000; maxElemPerSet += 1000) {
				OneLoop(numSets, minElemPerSet, maxElemPerSet, maxBatchId);
			}
		}
	}
}
