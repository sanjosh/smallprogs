#pragma once

#include <boost/intrusive/hashtable.hpp>
#include <boost/intrusive/list.hpp>
#include <sstream>
#include <string>
#include <glog/logging.h>

namespace bi = boost::intrusive;

/**
 * Keep Queue of entries in increasing seqnum order
 * which is also indexed (hash table) by key for fast lookup
 * When queue entries are deleted from front, also 
 * unlink them from the hash table
 */
class IndexedQueue {
	private:

	struct list1_tag;

	/**
	 * store list ptr using member hook
	 * store hashtable ptr using base hook
	 */
 	public:
	class Node : public bi::unordered_set_base_hook<> {
		public:
		int key_;
		int seqnum_;
		bi::list_member_hook<bi::tag<list1_tag>> listptr_;

	};

	// List
	typedef bi::member_hook<Node, bi::list_member_hook<bi::tag<list1_tag>>, 
		&Node::listptr_> MemberHookOption;
	typedef bi::list<Node, MemberHookOption> NodeList;
	NodeList list_;

	// Hash table
	static constexpr int kNumBuckets = 113;
	bi::hashtable<Node>::bucket_type baseBuckets[kNumBuckets];
	bi::hashtable<Node> hashTable;

	public:

	explicit IndexedQueue();

	IndexedQueue(const IndexedQueue&) = delete;
	void operator = (const IndexedQueue&) = delete;
	IndexedQueue(IndexedQueue&&) = delete;
	void operator = (IndexedQueue&&) = delete;

	void insert(int key, int seqnum);

	void deleteTill(int seqnum);

	std::string print() const;
};

// hash func for Node
inline size_t hash_value(const IndexedQueue::Node& b) {
	boost::hash<int> hasher;
	return hasher(b.key_);
}

// equal op for Node
inline bool operator ==(const IndexedQueue::Node& a, const IndexedQueue::Node& b) {
	return a.key_ == b.key_;
}
