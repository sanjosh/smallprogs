#include <boost/intrusive/hashtable.hpp>
#include <boost/array.hpp>
#include <boost/intrusive/list.hpp>
#include <iostream>

using namespace boost::intrusive;

struct list1_tag;

class Node : public unordered_set_base_hook<> {
	public:
	int val;
	list_member_hook<tag<list1_tag>> list_;
};

size_t hash_value(const Node& b) {
	boost::hash<int> hasher;
	return hasher(b.val);
}
bool operator ==(const Node& a, const Node& b) {
	return a.val == b.val;
}

typedef member_hook<Node, list_member_hook<tag<list1_tag>>, &Node::list_> MemberHookOption;

typedef boost::intrusive::list<Node, MemberHookOption> NodeList;
boost::intrusive::hashtable<Node>::bucket_type baseBuckets[113];
boost::intrusive::hashtable<Node> hashTable(hashtable<Node>::bucket_traits(baseBuckets, 113));

int main() {
	Node *aptr = new Node;
	std::cout << sizeof(Node) << std::endl;
	NodeList list;

	aptr->val = 5;
	list.push_back(*aptr);
	auto iter = hashTable.insert_equal(*aptr);

	for (auto& elem : list) {
		std::cout << elem.val <<  std::endl;
	}

	list.pop_front();
	hashTable.erase(iter);
	std::cout << list.size() << "," << hashTable.size() << std::endl;
	delete aptr;
};
