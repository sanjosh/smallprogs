/*
 * g++ -std=c++11 <file>
 * this code uses 64-bit morton code
 * It changes the MortonCode generated based on MyRow::NumCol 
 */

#include "morton.h"
#include <unistd.h>
#include <strings.h>
#include <cassert>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>

struct MyRow
{
  static constexpr uint32_t NumCol = 16;
  uint8_t a[NumCol];
  MortonCode64 code_{0};
  bool codeInited_ = false;

  MyRow(const std::vector<uint32_t>& vec)
  {
    bzero(a, sizeof(a));
    assert(vec.size() == NumCol);
    for (uint32_t idx = 0; idx < vec.size(); idx ++)
    {
      a[idx] = vec[idx];
    }
    code_ = MortonEncode32(a, NumCol);
    //std::cout << "code=" << std::hex << code_ << std::dec << std::endl;
    codeInited_ = true;
  }

  MortonCode code() const
  {
    assert(codeInited_);
    return code_;
  }

  bool operator < (const MyRow& other) const
  {
    //std::cout << "comparing " << code() << " with " << other.code() << std::endl;
    return code() < other.code();
  }

  friend std::ostream& operator << (std::ostream& ostr, const MyRow& r)
  {
    ostr << "{" << r.code() << ":";
    for (uint32_t idx = 0; idx < NumCol; idx ++) {
      ostr << (uint32_t) r.a[idx] << ",";
    }
    ostr << "}";
	return ostr;
  }

  void diff(const MyRow& other) const
  {
  }
};


/*
 * Possible final algo
 * use online approx algo for computing quantiles
 * find one for each datatype
 * what to do about strings ?
 *
 * for each row
 * {
 *   update quantiles for each col
 * }
 * for each row
 * {
 *   assign relative_pos based on quantiles for each col
 *   generate morton code from all col's relative_pos
 * }
 * sort table based on morton code
 */

constexpr uint32_t MaxRangeForEachCol = (0x1 << ((sizeof(MortonCode64) * 8) / MyRow::NumCol));

int main(int argc, char* argv[])
{
  size_t NumRows = pow(2, MyRow::NumCol);

  if (argc > 1) {
    NumRows = atoi(argv[1]);
  }

  std::mt19937 seedGen(getpid());
  std::uniform_int_distribution<uint32_t> numGen(0, MaxRangeForEachCol);

  typedef std::vector<MyRow> Table;

  Table table;

  // Enumerate all the combinations of possible columns
  for (uint32_t idx = 0; idx < NumRows; idx ++)
  {
    std::vector<uint32_t> arr;
    //std::generate_n(std::back_inserter(arr), MyRow::NumCol, [&] () -> uint32_t {return numGen(seedGen);});
    //
    //std::cout <<  "idx=" << idx << "{";
    for (uint32_t col = 0; col < MyRow::NumCol; col ++)
    {
      // if the bit-rep of i-th row has j-th bit set
      // set the j-th col for i-th row 
      auto bit = (((0x1 << col) & idx) >> col);
      //std::cout << bit << ",";
      arr.push_back(bit);
    }
    //std::cout << "}" << std::endl;

    MyRow a(arr);
    table.push_back(a);
  }

  // Sort table based on Morton code
  std::sort(table.begin(), table.end());

  // Print the rows sorted by Morton code
  for (auto& row : table) {
    std::cout << row << std::endl;
  }
}
