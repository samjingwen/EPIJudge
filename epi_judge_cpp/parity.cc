#include "test_framework/generic_test.h"

std::vector<uint16_t> generateParityTable() {
    std::vector<uint16_t> result(1 << 16);
    for (uint32_t i = 0; i < (1 << 16); ++i) {
        uint32_t x = i;

        short current = 0;
        while (x) {
            current ^= 1;
            x &= (x - 1);
        }
        result[i] = current;
    }

    return result;
}

static const std::vector<uint16_t> precomputed_parity = generateParityTable();

short Parity(unsigned long long x) {
    const int kWordSize = 16;
    const int kBitMask = 0xFFFF;

    return static_cast<short>(
            precomputed_parity[x & kBitMask] ^
            precomputed_parity[(x >> (1 * kWordSize)) & kBitMask] ^
            precomputed_parity[(x >> (2 * kWordSize)) & kBitMask] ^
            precomputed_parity[(x >> (3 * kWordSize)) & kBitMask]
    );
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
