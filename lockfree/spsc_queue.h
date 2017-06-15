#include <atomic>

/**
 * single producer single consumer
 */

struct Node {
	int64_t value_{-1};
	Node* next_{nullptr};

	Node(int64_t v) : value_(v) {}
};

class SPSCQueue {

	std::atomic<Node*> tail_;
	std::atomic<Node*> head_;

	public:

	SPSCQueue() {
		head_ = tail_ = new Node(-1);
	}
	
	// only moves tail
	void enqueue(int64_t val) {
		Node* n = new Node(val);
		tail_.load()->next_ = n;
		// dequeue can happen here
		tail_.store(n);
	}

	// only moves head
	int64_t dequeue() {
		// first node is always the sentinel
		Node* oldHead = head_.load();
		if (oldHead->next_ == nullptr) {
			sched_yield();
			return -1;
		}
		Node* n = oldHead->next_;
		int64_t ret = n->value_;
		head_.store(n);
		delete oldHead;
		return ret;
	}
};
