#include <iostream>
using namespace std;

#define ALPHABET_SIZE 26

class Trie;

class Node
{
    bool wordEnd;
    Node* list[ALPHABET_SIZE];

    public:
    Node()
    {
        wordEnd = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            list[i] = NULL;
    }

    friend class Trie;
};

class Trie
{
    Node* root;

    public:

    Trie()
    {
        root = new Node;
    }

#define INDEX(a) (a - 'a') // only lowercase for now

    void insert(const string& newStr)
    {
        Node* parent = root;
        for (int i = 0; i < newStr.size(); i++)
        {
            int index = INDEX(newStr[i]);
            Node* n = parent->list[index];
            if (!n)
            {
                parent->list[index] = n = new Node;
            }
            parent = n;
        }
        parent->wordEnd = true;
    }

    bool search(const string& findStr)
    {
        Node* parent = root;
        Node* n = NULL;
        bool found = false;

				if (!parent) return false;

        for (int i = 0; i < findStr.size(); i++)
        {
            n = parent->list[INDEX(findStr[i])];
            if (!n) 
            {
                break;
            }
            parent = n;
        }
        if (n)
        {
            found = n->wordEnd;
        }
        return found;
    }
};

int main()
{
    Trie tt;

    string list[] = {"abc", "abce", "def", "ghi", "jkl" };
    int len = sizeof(list)/sizeof(list[0]);

    for (int i = 0; i < len; i++)
    {
        tt.insert(list[i]);
    }

#define SRCH(STR) cout << "str=" << STR << " was found=" << tt.search(STR) << endl;
    
    SRCH("ab");
    SRCH("abc");
    SRCH("abcd");
    SRCH("abce");
    SRCH("def");
    SRCH("deef");
}


