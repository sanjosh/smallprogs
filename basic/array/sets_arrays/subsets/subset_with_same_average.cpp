/*

for array A

for subset B of k elements to have same average

Average(A) = Average(B) = 

Sum A1...Ak/n = Sum of B1...Bk/k = 

Exists k such that Sum of B1...Bk = k * Average

Do this until Sum of B1...Bk reaches (Average * n/2)

one elem : find element which is near equal to Average
two elem : find B1 < average and B2 > average such that (B1+B2)/2 = average
three elem B1...B3 : find (B1, B2) < average whose sum equal to (average * 3 - B3)
four elem B1...B4 : find (B1, B2, B3) < average whose sum equal to (average * 4 - B4)

when is this division not possible : is a quick check possible ?
when distribution is skewed

if len is odd, sum must be odd, 

median = middle element
mode = occurs most frequent
Quartile  = 25 perc of values below this

IQR = Q3 - Q1
outlier is point outside the interval [Q1−1.5xIQR, Q3+1.5xIQR].

five number summary

Matching Average results in a constraint which forces 

1. sum(set) to be integer multiple of len(set) on both sides
      otherwise average of sum divided by k1, k2 will leave fractions which can never be equal
      but 49/7 = 21/3
2. unless k1 is multiple of k2 - or does it mean gcd(k1, k2) > 1 ??
      if len(set1) = k x len(set2), then it means sum(set2) = k x sum(set1)
      24/4 = 36/6 

let k = gcd(len_set1, len_set2)
then atleast one average must be divisible by len_set1 or len_set2 
Counterexample - 4/4 = 6/6

if both sets equal, sum is equal


*/

#include <iostream>
#include <set>
#include <vector>
#include <cmath>

using namespace std;

int getSum(const std::set<int>& a)
{
    int sum = 0;
    for (auto iter = a.begin(); iter != a.end(); ++iter)
    {
        sum += *iter;
    }
    return sum;
}

void printSet(const std::set<int>& a, std::string annot)
{
        cout << annot;
        for (auto iter = a.begin(); iter != a.end(); ++iter) {
            cout << *iter << ",";
        }
        cout << endl;
}


bool checkMatch(int sum_a, int sum_b, int size_a, int size_b) 
{
    if ((sum_a > 0 && sum_b > 0) && ((size_a * sum_b) == (size_b * sum_a )))
    {
        //cout << "found " << size_b << "," << sum_a << ":" << size_a << "," << sum_b << endl;
        return true;
    }
    return false;
}

bool SameAverage(std::set<int>& a, std::set<int>& b)
{
    printSet(a, "trying ");
    int sum_a = getSum(a);    
    int sum_b = getSum(b);    

    return checkMatch(sum_a, sum_b, a.size(), b.size());
}

struct SubsetGen
{
    int iter_ = 0;
    int end_ = 0;
    std::vector<int> l;

    explicit SubsetGen(const std::vector<int> &input)
    {
       this->l = input; 
       this->end_ = 1 << this->l.size();
    }

    void begin()
    {
        this->iter_ = 0;
    }

    bool end() const
    {
        return this->iter_ == this->end_;
    }

    void getNext(std::set<int> &a, std::set<int>& b)
    {
        a.clear();
        b.clear();
        this->iter_ ++;
        for (int i = 0; i < this->l.size(); i ++) {
            if ((1 << i) & this->iter_) {
                a.insert(this->l[i]);
            } else {
                b.insert(this->l[i]);
            }
        }
    }
};

int main()
{
    std::vector<int> total = {3, 4, 5, 8};

    SubsetGen s(total);
    for (s.begin(); !s.end(); )
    {
        std::set<int> a;
        std::set<int> b;
        s.getNext(a, b);
        int ret = SameAverage(a, b);
        if (ret == true) {
            printSet(a, "FOUND ");
        }
    }
}
