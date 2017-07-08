#include "IndexedQueue.h"

IndexedQueue::IndexedQueue() 
	: hashTable(bi::hashtable<Node>::bucket_traits(baseBuckets, kNumBuckets)) {
}

void IndexedQueue::insert(int key, int seqnum) {
	Node *aptr = new Node;
	VLOG(1) << "alloc " << (void*)aptr;
	aptr->seqnum_ = seqnum;
	aptr->key_ = key;

	list_.push_back(*aptr);
	auto iter = hashTable.insert_equal(*aptr);
	(void) iter;
}

void IndexedQueue::deleteTill(int seqnum) {
	do {
		if (list_.size() == 0) {
			break;
		}
		Node& n = list_.front();
		if (n.seqnum_ >= seqnum) {
			break;
		}
		VLOG(1) << "delete seqnum=" << n.seqnum_ << ",ptr=" << (void*)&n;
		list_.pop_front();
		hashTable.erase(n);
		delete &n;
	} while (1);
}

std::string IndexedQueue::print() const {
	std::ostringstream os;
	for (auto& elem : list_) {
		os << elem.seqnum_ << "," << elem.key_ << std::endl;
	}
	return os.str();
}
