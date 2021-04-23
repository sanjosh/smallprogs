
#include <iostream>
#include <queue>

using namespace std;

struct TNode
{
    int value_;
    TNode* left_ = nullptr;
    TNode* right_ = nullptr;

    explicit TNode(int val) {
        this->value_ = val;
    }
};

void printLevelOrder(TNode* root) {
    std::queue<TNode*> q;

    q.push(root);

    while (q.size()) {

        int nodeCount = q.size();
        cout << nodeCount << ":";
        while (nodeCount) {
            TNode* p = q.front();
            cout << p->value_ << ",";
            q.pop();

            if (p->left_) {
                q.push(p->left_);
            }
            if (p->right_) {
                q.push(p->right_);
            }
            nodeCount --;
        }
        cout << endl;
    }
}


int main() {
    TNode* root = new TNode(5);
    root->left_ = new TNode(2);
    root->right_ = new TNode(8);

    root->left_->left_ = new TNode(1);
    root->left_->right_ = new TNode(3);

    root->right_->left_ = new TNode(6);
    root->right_->right_ = new TNode(9);
    printLevelOrder(root);
}
