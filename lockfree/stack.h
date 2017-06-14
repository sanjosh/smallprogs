#include <atomic>
#include <cstdint>
#include <thread>

/**
 * Stack which uses compare and exchange (sequential consistency)
 */

struct Node
{
	int64_t key_ = 0;
	Node* next_{nullptr};
	std::thread::id owner_; // for debugging

	Node(int64_t& key, Node* next) : key_(key), next_(next) {
		owner_ = std::this_thread::get_id();	
	}
};

struct Stack
{
	std::atomic<Node*> head_{nullptr};
	std::atomic<size_t> size_ {0};

	void push(int64_t key) {
		Node* oldHead = head_.load();
		Node* newNode = new Node(key, oldHead);
		while (!head_.compare_exchange_strong(oldHead, newNode)) {
			sched_yield();
			oldHead = head_.load();
			newNode->next_ = oldHead;
		}
		size_.fetch_add(1, std::memory_order_relaxed);
	};

	void pop(int64_t& key) {
		Node* oldHead = head_.load();
		while (!oldHead) {
			sched_yield();
			oldHead = head_.load();
		}
		Node* nextNode = oldHead->next_;
		while (!head_.compare_exchange_strong(oldHead, nextNode)) {
			do {
				oldHead = head_.load();
				if (!oldHead) {
					sched_yield();
				}
			} while (!oldHead);
			nextNode = oldHead->next_;
		}
		key = oldHead->key_;
		delete oldHead; 
		size_.fetch_sub(1, std::memory_order_relaxed);
	}

	size_t size() const {
		return size_;
	}
};

