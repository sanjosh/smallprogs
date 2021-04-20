#include <iostream>
#include <vector>

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

  std::swap(arr[i-1], arr[j]);

  j = arr.size() - 1;
  // reverse array starting at i
  while (i < j) {
    std::swap(arr[i], arr[j]);
    i++;
    j--;
  }
  return true;
}

int main()
{
  std::vector<int> arr = {1, 2, 3};

  while (nextPerm(arr)) {
    for (auto elem : arr) {
      std::cout << elem;
    }
    std::cout << std::endl;
  }
}
