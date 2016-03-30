/*
 * https://en.wikipedia.org/wiki/Move-to-front_transform
 * g++ -std=c++11 MoveToFrontTransform.cpp
 * ./a.out <string>
 */
#include <string>
#include <vector>
#include <cassert>
#include <set>
#include <iostream>

using std::vector;
using std::set;

/*
  for each c in string
  {
    encoded += idx(c) in dict
    bring char to front of dict
  }
  return encoded
*/

vector<int> encode(const std::string& s, std::string dict)
{
  vector<int> encoded;
  for (auto c : s)
  {
    auto iter = dict.find(c);
    assert(iter != std::string::npos);
    encoded.push_back(iter);
    dict.insert(0, 1, c);
    dict.erase(iter + 1, 1);
  }
  return encoded;
}

/*
  for each number in encoded
  {
    emit char at dict[number]
    move dict[number] to front of list
  }
*/

std::string decode(vector<int>& v, std::string dict)
{
  std::string decoded;
  for (auto elem : v)
  {
    decoded.push_back(dict[elem]);
    dict.insert(0, 1, dict[elem]);
    dict.erase(elem + 1, 1);
  }
  return decoded;
}

int main(int argc, char* argv[])
{
  std::string input = "dgegbdadadb";
  if (argc > 1)
  {
    input = argv[1];
  }
  // sort and remove duplicates
  std::set<char> uniqsort(input.begin(), input.end()); 
  std::string dict(uniqsort.begin(), uniqsort.end());

  auto e = encode(input, dict);
  auto output = decode(e, dict);
  assert(input == output);
  std::cout << "output=" << output << std::endl;
}
