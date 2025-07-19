#include "test_framework/generic_test.h"

constexpr uint8_t swapBits(uint8_t x, int i, int j) {
  if ((x >> i & 1) != (x >> j & 1)) {
    uint8_t mask = (1 << i) | (1 << j);
    x ^= mask;
  }

  return x;
}

constexpr unsigned long long reverseBits(uint8_t num) {
  for (int i = 0; i < 4; ++i) {
    num = swapBits(num, i, 7 - i);
  }
  return num;
}

constexpr std::array<unsigned long long, 1 << 8> generateReverseBitTable() {
  std::array<unsigned long long, 1 << 8> table{};
  for (uint32_t i = 0; i < (1 << 8); ++i) {
    table[i] = reverseBits(i);
  }
  return table;
}

constexpr auto precomputed_reverse = generateReverseBitTable();

unsigned long long ReverseBits(unsigned long long x) {
  const int kWordSize = 8;
  const int kBitMask = 0xFF;
  const int kChunks = 64 / kWordSize;

  auto result = precomputed_reverse[x & kBitMask]
                << ((kChunks - 1) * kWordSize);

  for (int i = 1; i < kChunks; ++i) {
    result |= (precomputed_reverse[(x >> (i * kWordSize)) & kBitMask]
               << ((kChunks - 1 - i) * kWordSize));
  }

  return result;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
