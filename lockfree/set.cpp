#include "set.h"
#include <limits>

// C++ version of nonblocking sync described in 
// Art of Multiprocessor programming Herlihy Shalit Chap 9

Set::Set() {
    head = new Node(std::numeric_limits<int64_t>::min());
    tail = new Node(std::numeric_limits<int64_t>::max());
    Node* h = head;
    h->next.store(tail);
}

Set::Bound Set::find(Node* head, int64_t key) {
    Node* pred = nullptr;
    Node* curr = nullptr;
    Node* succ = nullptr;
    bool marked = false;

retry:
    while (true) {
        pred = head;
        curr = pred->next.load();
        while (curr) {
            succ = curr->next.load(marked); 
            while (succ && marked) {
                // if node is deleted, unlink it
                bool snip = pred->next.compare_exchange_strong(curr, succ, false, false);
                if (not snip) {
                    goto retry;
                }
                delete curr;
                curr = succ;
                succ = curr->next.load(marked); 
            }
            if (curr->key >= key) {
                return Bound(pred, curr);
            }
            pred = curr;
            curr = succ;
        }
    }
}

bool Set::insert(int64_t key) {
    Node *node = new Node(key);
    while (true) {
        Bound bound = find(head, key);
        Node *pred = bound.pred;
        Node *curr = bound.curr;
        if (curr->key == key) {
            return false;
        } else {
            node->next.store(curr, false);
            if (pred->next.compare_exchange_strong(curr, node, false, false)) {
                return true;
            }
        }
    }
}

bool Set::remove(int64_t key) {
    while (true) {
        Bound bound = find(head, key);
        Node *pred = bound.pred;
        Node *curr = bound.curr;
        if (curr->key != key) {
            return false;
        } else {
            Node *succ = curr->next.load();
            // mark node as deleted
            bool snip = curr->next.compare_exchange_strong(succ, succ, false, true);
            if (!snip) {
                continue;
            }
            // unlink node
            pred->next.compare_exchange_strong(curr, succ, false, false);
            return true;
        }
    }
}

bool Set::contains(int64_t key) {
    bool marked;
    Node *curr = head;
    while (curr->key < key) {
        curr = curr->next.load();
        curr->next.load(marked);
    }
    return (curr->key == key) && (not marked);
}
