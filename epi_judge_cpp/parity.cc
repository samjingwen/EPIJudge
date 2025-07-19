#include "test_framework/generic_test.h"

constexpr std::array<short, 1 << 8> generateParityTable() {
  std::array<short, 1 << 8> table{};
  for (uint16_t i = 0; i < table.size(); ++i) {
    auto x = i;

    short current = 0;
    while (x) {
      current ^= 1;
      x &= (x - 1);
    }
    table[i] = current;
  }

  return table;
}

constexpr auto precomputed_parity = generateParityTable();

short Parity(uint64_t x) {
  const int kWordSize = 8;
  const int kBitMask = (1 << kWordSize) - 1;
  const int kChunks = 64 / kWordSize;

  short result = precomputed_parity[x & kBitMask];

  for (int i = 1; i < kChunks; ++i) {
    result ^= precomputed_parity[(x >> (i * kWordSize)) & kBitMask];
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
