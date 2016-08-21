/*
 * without knowing distribution in advance
 * http://stackoverflow.com/questions/11944050/online-entropy-evaluation-algorithm
 *
 */

#include <sys/types.h> // getpid
#include <unistd.h> // getpid

#include <cmath> // log
#include <random> // uniform_distrib
#include <iostream>
#include <map>

template <class Key>
class Entropy
{
  std::map<Key, uint32_t> keyCount;
  uint32_t totalCount{0};

  public:

  void addValue(Key k)
  {
    keyCount[k] ++;
    totalCount ++;
  }

  // average bits per symbol
  double getEntropy()
  {
    double entropy = 0;

    for (auto item : keyCount)
    {
      double prob = ((double)item.second/totalCount);
      entropy -= prob * std::log2(prob);
    }
    return entropy;
  }

  double maxEntropy()
  {
    return std::log2(totalCount);
  }
};

int main(int argc, char* argv[])
{
  {
    Entropy<uint32_t> ent;
  
    std::mt19937 seedGen(::getpid());
    std::uniform_int_distribution<uint32_t> toss(0, 32768);
   
    for (int i = 0; i < 1000; i ++) {
      ent.addValue(toss(seedGen));
    }

    std::cout 
      << "entropy=" << ent.getEntropy() 
      << ":max=" << ent.maxEntropy()
      << std::endl;
  }
  
  {
    Entropy<uint32_t> ent;
    for (int i = 0; i < 1000; i ++) {
      ent.addValue(i/100);
    }

    std::cout 
      << "entropy=" << ent.getEntropy() 
      << ":max=" << ent.maxEntropy()
      << std::endl;
  }
}
