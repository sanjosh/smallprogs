
// merge algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::merge, std::sort
#include <vector>       // std::vector

bool Comp(int a, int b)
{
    return a > b;
}

int main () {
  int first[] = {5,10,15,20,25};
  int second[] = {50,40,30,20,10};
  std::vector<int> v(10);

  std::sort (first,first+5, Comp);
  std::sort (second,second+5, Comp);
  std::merge (first,first+5,second,second+5,v.begin(), Comp);

  std::cout << "The resulting vector contains:";
  for (std::vector<int>::iterator it=v.begin(); it!=v.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
