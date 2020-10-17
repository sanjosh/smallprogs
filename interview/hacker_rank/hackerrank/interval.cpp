
/**
	https://www.hackerrank.com/challenges/crush
 */
#include <map>

struct Val {
	int val;
};

struct Key {
	int start;
	int end;

	Key(int s, int e) : start(s), end(e) {}
};

struct LessThan {
  bool operator () (const Key& a, const Key& b) const {
		return a.start < b.start;
  }
};

typedef std::map<Key, Val, LessThan> Ranges;
Ranges ranges;

std::list<Key> intersect(Key& key, Key& current) {
	std::list<Key> keys;
	if (key.start < current.start) {
		if (key.end < current.end) {
			keys.push_back(key);
		} else if (key.end == current.end) {
			// intersect
			keys.emplace_back(key.start, current.start);
			keys.emplace_back(current.start, current.end);
		} else {
			// 3 elem
			keys.emplace_back(key.start, current.start);
			keys.emplace_back(current.start, current.end);
			keys.emplace_back(current.end, key.end);
		}
	}	else if (key.start == current.start) {
		if (key.end < current.end) {
			keys.push_back(key);
			keys.emplace_back(key.end, current.end);
		} else if (key.end == current.end) {
			// same
			keys.emplace_back(key.start, key.end);
		} else {
			// 2 elem
			keys.emplace_back(key.start, current.end);
			keys.emplace_back(current.end, key.end);
		}
	} else if (key.start > current.start) { 
		// TODO
		if (key.end < current.end) {
			keys.push_back(key);
		} else if (key.end == current.end) {
			// intersect
			keys.emplace_back(key.start, current.start);
			keys.emplace_back(current.start, current.end);
		} else {
			// 3 elem
			keys.emplace_back(key.start, current.start);
			keys.emplace_back(current.start, current.end);
			keys.emplace_back(current.end, key.end);
		}
	}
}

void insert(Key &key, int val) {
	auto iter = ranges.lower_bound(start);

	while (iter.end < key.start) {
		auto list = intersect(key, iter.first);
		key = list.lastelem
		list = list - last
		delete iter
		for each list {
			ranges.insert(key, val) // incr if exists
		}
  }
	insert key
}

int main(int argc, char* argv[]) {

	int n;
  int m;

  cin >> n >> m;
  for(int a0 = 0; a0 < m; a0++){
    int a;
    int b;
    int k;
    cin >> a >> b >> k;
  }
  return 0;
}
