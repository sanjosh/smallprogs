#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Node
{
    bool terminal = false;
    Node* child[26]; // unique_ptr

    explicit Node()
    {
        for (int i = 0; i < 26; i++)
        {
            child[i] = nullptr;
        }
    }
};

struct Trie
{
    Node* root = nullptr;

    explicit Trie()
    {
        root = new Node();
    }

    void insert(const string& str)
    {
        int idx = 0;
        Node* cur = root;
        bool found = false;

         while (cur->child['z' - str[idx]]) {
            cur = cur->child['z' - str[idx]];
            idx ++;
            if (idx == str.size()) {
                found = true;
                break;
            }
        }
        if (found) {
            // two cases : longer str or str ends at this point
            cur->terminal = true; 
            return;
        }
        // case : shorter str
        for (; idx < str.size(); idx ++)
        {
            auto p = new Node();
            cur->child['z' - str[idx]] = p;
            cur = p;
        }
        cur->terminal = true;
    }

    bool exists(const string& str) const
    {
        int idx = 0;
        Node* cur = root;
        bool found = false;

        while (cur->child['z' - str[idx]]) {
            cur = cur->child['z' - str[idx]];
            idx ++;
            if (idx == str.size() && cur->terminal) {
                found = true;
                break;
            }
        }
        return found;
    }
};

int main()
{
    Trie* t = new Trie();
    t->insert("abc");
    t->insert("def");
    t->insert("ab"); // insert shorter
    t->insert("abcdefgh"); // insert longer

    vector<string> search = { "abc", "abcdefgh", "zyz", "def" };

    for (int i = 0; i < search.size(); i++)
    {
        cout << t->exists(search[i]) << endl;
    }

}
