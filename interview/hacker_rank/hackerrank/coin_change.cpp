// https://www.hackerrank.com/challenges/coin-change
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <unordered_map>

std::vector<long> CoinList;

struct Coins {
	long value{-1};
	long copies{-1};

	Coins(long v, long c) : value(v), copies(c) {}
};

typedef std::list<Coins> CoinSet;

struct MemoKey {
	long coinIndex;
	long sumLeft;

	MemoKey(long c, long s) {
		coinIndex = c;
		sumLeft = s;
	}

  bool operator == (const MemoKey& other) const {
		return coinIndex == other.coinIndex 
			&& sumLeft == other.sumLeft;
	}
};

struct MemoKeyHash {
	size_t operator () (const MemoKey& k) const {
		return std::hash<long>()(k.coinIndex) ^ std::hash<long>()(k.sumLeft);
	}
};

std::unordered_map<MemoKey, long, MemoKeyHash> memos;

long findSum(const CoinSet& haveCoins, long sumLeft, long coinIndex)
{
	if (sumLeft == 0) {
		return 1;
	}
	if (coinIndex >= CoinList.size()) {
		return 0;
	}

	if (CoinList[coinIndex] > sumLeft) {
		// if this coin is larger than sumLeft, try next coin
		return findSum(haveCoins, sumLeft, coinIndex + 1);
	} else {
    long total_combo = 0;
		MemoKey k(coinIndex, sumLeft);
		auto iter = memos.find(k);
		if (iter != memos.end()) {
			total_combo = iter->second;
		} else {
			long start = 0; // no coin is also possible
			if (coinIndex == CoinList.size() - 1) { 
				start = sumLeft/CoinList[coinIndex]; // take all if last elem
			}
			const long end = sumLeft/CoinList[coinIndex];
			for (long num_copies = start; num_copies <= end; num_copies++) {
				if (sumLeft >= num_copies * CoinList[coinIndex]) {
					const long next_sum = sumLeft - num_copies * CoinList[coinIndex];
					CoinSet newList(haveCoins);
					newList.emplace_back(CoinList[coinIndex], num_copies);
					total_combo += findSum(newList, next_sum, coinIndex + 1);
				}
			}
			memos.insert({k, total_combo});
		}
    return total_combo;
	}
}

long getWays(long n, std::vector<long> c) {
  std::sort(c.begin(), c.end(), std::greater<long>());
	CoinList = c;
	long sumLeft = n;
	CoinSet haveCoins;
	long num = findSum(haveCoins, sumLeft, 0);
	std::cout << num << std::endl;
	return num;
}

int main(int argc, char* argv[])
{
	int n;
  int m;
  std::cin >> n >> m;
  std::vector<long> c(m);
  for(int c_i = 0; c_i < m; c_i++){
     std::cin >> c[c_i];
  }
  // Print the number of ways of making change for 'n' units using coins having the values given by 'c'
  long ways = getWays(n, c);
  return 0;
}
