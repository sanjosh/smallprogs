#include <cstdint>
#include <algorithm> // std::min
#include <cassert> // std::min

/*
 * Asger Hoedt
 * http://asgerhoedt.dk/?p=276
 *
 * http://graphics.stanford.edu/~seander/bithacks.html
 * http://stackoverflow.com/questions/1024754/how-to-compute-a-3d-morton-number-interleave-the-bits-of-3-ints
 *
 * http://www.forceflow.be/2013/10/07/morton-encodingdecoding-through-bit-interleaving-implementations/
 */

typedef uint32_t MortonCode;
typedef uint64_t MortonCode64;

// input has 2 bytes = 16 bits
uint32_t SeparateBy1(uint32_t x) {
  x &= 0x0000ffff;                  // x = ---- ---- ---- ---- fedc ba98 7654 3210
  x = (x ^ (x <<  8)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210
  x = (x ^ (x <<  4)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
  x = (x ^ (x <<  2)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10
  x = (x ^ (x <<  1)) & 0x55555555; // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
  return x;
}

// input has 7 bits
// Caution 7 x 5 = 35, so 5-dim codes will overflow 32-bit num
uint32_t SeparateBy4(uint32_t x) {
  x &= 0x0000007f;                  // x = ---- ---- ---- ---- ---- ---- -654 3210
  x = (x ^ (x << 16)) & 0x0070000F; // x = ---- ---- -654 ---- ---- ---- ---- 3210
  x = (x ^ (x <<  8)) & 0x40300C03; // x = -6-- ---- --54 ---- ---- 32-- ---- --10
  x = (x ^ (x <<  4)) & 0x42108421; // x = -6-- --5- ---4 ---- 3--- -2-- --1- ---0
  return x;
}

// input has 2 bits
// pack 32 of these 2-bit columns into a 64-bit num
MortonCode64 SeparateBy31(MortonCode64 x) {
  x &= 0x000000000000003;                  // x = ---- ---- ---- ---- ---- ---- ---- --32
  x = (x ^ (x << 31)) & 0x0100000001;      // x = ---- ---- ---- ---3 ---- ---- ---- ---2
  return x;
}

// for n-dim, you have to separate by (n-1)
MortonCode MortonCode2(uint32_t x, uint32_t y) {
  return SeparateBy1(x) | (SeparateBy1(y) << 1);
}

MortonCode MortonCode5(uint32_t x, uint32_t y, uint32_t z, uint32_t u, uint32_t v) {
  return SeparateBy4(x) | (SeparateBy4(y) << 1) | (SeparateBy4(z) << 2) | (SeparateBy4(u) << 3) | (SeparateBy4(v) << 4);
}

// for 32 columns, we must separate input column bits by 31
MortonCode64 MortonEncode32(uint8_t* x, uint32_t numcol) {
  MortonCode64 code = 0;
  bool allInputZero = true;
  for (auto idx = 0; idx < numcol; idx ++)
  {
    code |= (SeparateBy31(x[idx]) << idx);
    if (x[idx]) {
      allInputZero = false;
    }
  }
  if (code == 0) {
    assert(allInputZero);
    // otherwise there is a bit manipulation bug
  }
  return code;
}

uint32_t CompactBy1(uint32_t x) {
  x &= 0x55555555;                  // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
  x = (x ^ (x >>  1)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10
  x = (x ^ (x >>  2)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
  x = (x ^ (x >>  4)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210
  x = (x ^ (x >>  8)) & 0x0000ffff; // x = ---- ---- ---- ---- fedc ba98 7654 3210
  return x;
}

uint32_t CompactBy4(uint32_t x) {
  x &= 0x42108421;                  // x = -6-- --5- ---4 ---- 3--- -2-- --1- ---0
  x = (x ^ (x >>  4)) & 0x40300C03; // x = -6-- ---- --54 ---- ---- 32-- ---- --10
  x = (x ^ (x >>  8)) & 0x0070000F; // x = ---- ---- -654 ---- ---- ---- ---- 3210
  x = (x ^ (x >> 16)) & 0x0000007F; // x = ---- ---- ---- ---- ---- ---- -654 3210
  return x;
}

void MortonDecode2(MortonCode c, uint32_t& x, uint32_t& y) {
  x = CompactBy1(c);
  y = CompactBy1(c >> 1);
}

void MortonDecode5(MortonCode c, uint32_t& x, uint32_t& y, uint32_t& z, uint32_t& u, uint32_t& v) {
  x = CompactBy4(c);
  y = CompactBy4(c >> 1);
  z = CompactBy4(c >> 2);
  u = CompactBy4(c >> 3);
  v = CompactBy4(c >> 4);
}

#ifdef NOT_OPTIMAL
MortonCode Minimum2(MortonCode lhs, MortonCode rhs) {
 uint32_t lhsX, lhsY, rhsX, rhsY;

 // Decode the left hand side coordinates.
 MortonDecode2(lhs, lhsX, lhsY);

 // Decode the right hand side coordinates.
 MortonDecode2(rhs, rhsX, rhsY);

 // Find the minimum of the coordinates and re-encode.
 return MortonCode2(std::min(lhsX, rhsX), std::min(lhsY, rhsY));
}
#endif


MortonCode Minimum2(MortonCode lhs, MortonCode rhs) {
  // Isolate the encoded coordinates.
  uint32_t lhsX = lhs & 0x55555555; // lhsX = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
  uint32_t rhsX = rhs & 0x55555555; // rhsX = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
  uint32_t lhsY = lhs & 0xAAAAAAAA; // lhsY = f-e- d-c- b-a- 9-8- 7-6- 5-4- 3-2- 1-0-
  uint32_t rhsY = rhs & 0xAAAAAAAA; // rhsY = f-e- d-c- b-a- 9-8- 7-6- 5-4- 3-2- 1-0-
 
  // Find the minimum of the encoded coordinates and combine them into a single
  // word.
  return std::min(lhsX, rhsX) + std::min(lhsY, rhsY);
}

