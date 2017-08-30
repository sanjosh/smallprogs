#include <iostream>

template <typename Val>
struct Node
{
	Val val_;
	Node* left_{nullptr};
	Node* right_{nullptr};

	explicit Node(Val v) : val_(v) {}

	template <typename LambdaFunc>
	void post_order(LambdaFunc&& func) {
		if (left_) left_->post_order(func);
		if (right_) right_->post_order(func);
		func(this);
	}
};


int main()
{
	auto root = new Node<int>(1);
	root->left_ = new Node<int>(3);
	root->right_ = new Node<int>(4);

	auto printme = [](auto t) {
		std::cout << t->val_ << std::endl;
	};
	root->post_order(printme);

	int count = 0;
	auto is_leaf = [&count](auto t) {
		count += (not t->left_) and (not t->right_);
	};
	root->post_order(is_leaf);
	std::cout << "num leaf=" << count << std::endl;
}
