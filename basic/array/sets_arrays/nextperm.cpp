#include <iostream>
#include <vector>

using namespace std;

/*

(pivot = from right, find number which is less than previous)

Find the highest index i such that s[i] < s[i+1]. 
If no such index exists, the permutation is the last permutation.

(find farthest number to right which is greater than pivot)

Find the highest index j > i such that s[j] > s[i]. 
Such a j must exist, since i+1 is such an index.

Swap s[i] with s[j].

Reverse the order of all of the elements [i + 1, N]

https://stackoverflow.com/questions/1622532/algorithm-to-find-next-greater-permutation-of-a-given-string

*/

bool nextPerm(std::vector<int>& arr)
{
  int i = arr.size() - 1;

  while (i > 0 && (arr[i-1] >= arr[i])) {
    i--;
  }

  if (i <= 0) return false;

  // arr[i-1] is the pivot
  int j = arr.size() - 1;
  // find rightnost elem that exceeds pivot
  while (arr[j] <= arr[i-1]) {
    j--;
  }

  cout << i-1 << ":" << arr[i-1] << " swap " << j << ":" << arr[j] << endl;

  std::swap(arr[i-1], arr[j]);

  j = arr.size() - 1;
  // reverse array starting at i
  //cout << i << "," << j << endl;
  while (i < j) {
    std::swap(arr[i], arr[j]);
    i++;
    j--;
  }
  return true;
}

int main()
{
  std::vector<int> arr = {1, 2, 3, 4};

  while (nextPerm(arr)) {
    for (auto elem : arr) {
      std::cout << elem;
    }
    std::cout << std::endl;
  }
}
