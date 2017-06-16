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
		Node* newNode = new Node(key, nullptr);
		int attempt = 0;
		Node* oldHead = nullptr;
		do {
			if (attempt++) { sched_yield(); }
			oldHead = head_.load();
			newNode->next_ = oldHead;
		} while (not head_.compare_exchange_strong(oldHead, newNode));
		size_.fetch_add(1, std::memory_order_relaxed);
	};

	void pop(int64_t& key) {
		Node* oldHead = nullptr;
		Node* nextNode = nullptr;
		do {
			while (!(oldHead = head_.load())) {
				sched_yield();
			} 
			nextNode = oldHead->next_;
		} while (not head_.compare_exchange_strong(oldHead, nextNode));
		key = oldHead->key_;
		delete oldHead; 
		size_.fetch_sub(1, std::memory_order_relaxed);
	}

	size_t size() const {
		return size_;
	}
};

