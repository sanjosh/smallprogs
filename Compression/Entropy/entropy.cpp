#include <iostream>
#include <cmath>
#include <limits>
#include <map>
#include <vector>

// TODO Add code to compute redundancy = average code len - entropy
// TODO for char, specialize to "float arr[256]; as ProbMap"
// TODO add higher order entropy calc

// Entropy is lower bound on average number of bits per symbol
template <class Symbol>
struct Entropy
{
  typedef std::map<Symbol, float> ProbMap;
  typedef std::vector<Symbol> Message;

  ProbMap prob_;

  Entropy()
  {
  }

  int setProbability(const ProbMap& prob)
  {
    int ret = 0;

    // All probabilities should sum to zero
    float sum = 0.0;
    for (auto elem : prob)
    {
      sum += elem.second;
    }
    if (std::fabs(sum - 1.0f) > 3*std::numeric_limits<float>::epsilon())
    {
      std::cerr << "failed=" << sum - 1.0f << std::endl;
      ret = -EINVAL;
    } else {
      prob_ = prob;
      ret = 0;
    }
    return ret;
  }

  // TODO : replace vector by ForwardIterator
  // actual entropy of message ranges between [0, log_2(n)]
  // where n is message size
  // maxEntropy = log_2(n) is optional return value from this func
  int calc(const Message& block, float& entropy, float* maxEntropy = nullptr)
  {
    int error = 0;
    float H = 0.0;

    for (auto elem : block)
    {
      auto p = prob_.find(elem);
      if (p == prob_.end())
      {
        error = -EINVAL;
        break;
      }
      H += (-(p->second)) * std::log2(p->second);
    }
    if (error == 0)
    {
      entropy = H;
      if (maxEntropy) 
      {
        *maxEntropy = std::log2(block.size());
      }
    }
    return error;
  }
};


int main(int argc, char* argv[])
{
  Entropy<char> ent;

  Entropy<char>::ProbMap p;

  float prob = 1.0/26;
  for (int i = 0; i < 26; i++)
  {
    p.insert(std::make_pair<char, float>('a' + i, std::move(prob)));
  }

  ent.setProbability(p);

  Entropy<char>::Message b;
  for (int i = 0; i < 26; i++)
  {
    b.push_back('a' + i);
  }

  float h;
  float maxEnt;
  ent.calc(b, h, &maxEnt);

  std::cout << "average number of bits per symbol=" << h << std::endl;

  std::cout << "max=" << maxEnt << std::endl;
}


