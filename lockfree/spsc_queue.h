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

	Node* tail_;
	Node* head_;
	std::atomic<size_t> size_{0};

	public:

	size_t size() const {
		return size_;
	}

	SPSCQueue() {
		head_ = tail_ = new Node(-1);
	}
	
	// only moves tail
	void enqueue(int64_t val) {
		Node* n = new Node(size_);
		tail_->next_ = n;
		// dequeue can happen here - fine
		tail_ = n;
		size_.fetch_add(1, std::memory_order_relaxed);
	}

	// only moves head
	int64_t dequeue(bool& is_empty) {
		// first node is always the sentinel
		is_empty = false;
		Node* oldHead = head_;
		if (oldHead->next_ == nullptr) {
			is_empty = true;
			return -1;
		}
		Node* n = oldHead->next_;
		int64_t ret = n->value_;
		head_ = n;
		delete oldHead;
		size_.fetch_sub(1, std::memory_order_relaxed);
		return ret;
	}
};
