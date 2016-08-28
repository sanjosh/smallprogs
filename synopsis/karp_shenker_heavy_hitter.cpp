#include <map>
#include <iostream>
#include <cstdint>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>

bool isZero(uint32_t val)
{
  return val == 0;
}

struct KarpShenker
{
  std::map<uint32_t, int> freq_;
  float threshold_;

  KarpShenker(float threshold)
    : threshold_(threshold)
  {
  }

  void insert(uint32_t val)
  {
    freq_[val] ++;

    if (freq_.size() > 10)
    {
      for (auto& elem : freq_)
      {
        elem.second --;
      }

      auto iter = freq_.begin();

      // delete elem with zero counts
      int numDeleted = 0;
      for (; iter != freq_.end(); )
      {
        if (iter->second == 0) {
          freq_.erase(iter ++);
          numDeleted ++;
        } else {
          iter ++;
        }
      }
      std::cout << "numdeleted=" << numDeleted << std::endl;
    }
  }

  friend std::ostream& operator << (std::ostream& os, const KarpShenker& ks)
  {
    for (auto elem : ks.freq_)
    {
      os << elem.first << ":" << elem.second << std::endl;
    }
    return os;
  }
};

int main()
{
  KarpShenker ks(0.2);
  
  std::mt19937 seed(getpid());
  std::normal_distribution<double> distrib(500.0, 20.0);

  for (int i = 0; i < 1000; i++)
  {
    uint32_t idx = distrib(seed)/10;
    std::cout << idx << std::endl;
    ks.insert(idx);
  }
  std::cout << ks << std::endl;
}
