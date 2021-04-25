/**
    add two numbers represented as lists in reverse order and return another list

    https://leetcode.com/problems/add-two-numbers/
 */
#include <iostream>
#include <list>
using namespace std;

int getNumFromList(const std::list<int32_t>& l)
{
    int num = 0;
    int cur_base = 1;
    for (auto iter = l.cbegin(); iter != l.cend(); iter ++)
    {
        num += (*iter) * cur_base;
        cur_base = cur_base * 10;
    }
    return num;
}

std::list<int32_t> createList(const int32_t copy_num)
{
    int base = 10;
    std::list<int32_t> ret;
    int32_t num = copy_num; 
    while (num > 0) {
        const int digit = num % base;
        ret.push_back(digit);
        num = (num - digit) / base;
    }
    return ret;
}

std::list<int32_t> addTwoNumbers(const std::list<int32_t>& l1, const std::list<int32_t>& l2)
{
    const int f1 = getNumFromList(l1);
    const int f2 = getNumFromList(l2);
    return createList(f1 + f2);
}

int main() 
{
    std::list<int32_t> l1 = {9, 9, 9, 9};
    std::list<int32_t> l2 = {9, 9, 9, 9, 9, 9, 9};
    auto ret = addTwoNumbers(l1, l2);
    for (auto iter = ret.cbegin(); iter != ret.cend(); ++iter) 
    {
        std::cout << *iter;
    }
    cout << endl;
}
