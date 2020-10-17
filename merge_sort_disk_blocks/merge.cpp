#include <algorithm>
#include <vector>

using namespace std;

#include <iostream>
template <class Container>
void showSequence(const Container& s, const char* sep=" ", ostream& where=std::cout)
{
    typename Container::const_iterator iter = s.begin();
    while (iter != s.end())
    {
        where << *iter++ << sep;
    }
    where << std::endl;
}

template <class ForwardIterator, class T>
void iota(ForwardIterator first, ForwardIterator last, T value, T increment)
{
    while (first != last) 
    {
        *first ++ = value; 
        value += increment;
    }
}

struct diskblk
{
    int a;
    int file;
    int offset;

    public:
    diskblk() { a = 0;}
    diskblk(int in) { a = in;}
    int& operator *() {return a;}
    diskblk& operator += (const diskblk& val) { a+=val.a; return *this;}

    bool operator < (const diskblk& other) const
    {
        return (a < other.a);
    }

    friend ostream& operator <<(ostream& ostr, const diskblk& me)
    {
        ostr << me.a; return ostr;
    }
};

struct diskblkcompare
{
    bool operator () (const diskblk& lhs, const diskblk& rhs)
    {
        return lhs.a < rhs.a;
    }
};


namespace std
{
    template<> struct less<diskblk>
    {
       bool operator() (const diskblk& lhs, const diskblk& rhs)
       {
           return lhs.a < rhs.a;
       }
    };
}

int main()
{
    vector<diskblk> v1(512);
    iota(v1.begin(), v1.end(), diskblk(1), diskblk(3));
    showSequence(v1);

    vector<diskblk> v2(512);
    iota(v2.begin(), v2.end(), diskblk(0), diskblk(2));
    showSequence(v2);

    vector<diskblk> result(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());
    showSequence(result);
    
}




