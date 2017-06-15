#include <atomic>

/**
 * Herlihy Shavit - Art of Multiprocessor - 10.5
 */

struct Node {
	int64_t value_;
	std::atomic<Node*> next_;

	Node(int64_t v) : value_(v) {}
};

class Queue {

	std::atomic<Node*> tail_;
	std::atomic<Node*> head_;
	Node sentinel_;

	public:

	Queue() : sentinel_(-2) {
		tail_ = head_ = &sentinel_;
	}
	
	void enqueue(int64_t val) {

		Node* n = new Node(val);

		while (true) {
			Node* last = tail_.load();
			Node* next = last->next_.load();
			if (last == tail_.load()) {
				if (next == nullptr) {
					// set tail->next = new_node
					if (last->next_.compare_exchange_strong(next, n)) {
						// Move tail
						tail_.compare_exchange_strong(last, n);
						return;
					}
				} else {
					// other thread has not yet Moved tail
					tail_.compare_exchange_strong(last, n);	
				}
			}
		}
	}

	int64_t dequeue() {
		while (true) {
			Node* first = head_.load();
			Node* last = tail_.load();
			Node* next = first->next_.load();

			if (first == head_.load()) {
				if (first == last) {
					if (next == nullptr) {
						// queue is empty
						return -1;
					}
					// first elem inserted but tail was not yet moved by other thread
					tail_.compare_exchange_strong(last, next);
				} else {
					const int64_t v = next->value_;
					// move head to next
					if (head_.compare_exchange_strong(first, next)) {
						delete next;
						return v;
					}
				}
			}
		}
	}
};
