#include "test_framework/generic_test.h"

uint16_t reverseBits(uint16_t num) {
    uint16_t result = 0;
    for (int i = 0; i < 16; ++i) {
        result <<= 1;
        result |= (num & 1);
        num >>= 1;
    }
    return result;
}

std::vector<uint16_t> generateReverseBitTable() {
    std::vector<uint16_t> result(1 << 16);
    for (uint32_t i = 0; i < (1 << 16); ++i) {
        result[i] = reverseBits(i);
    }
    return result;
}

static const std::vector<uint16_t> precomputed_reverse = generateReverseBitTable();

unsigned long long ReverseBits(unsigned long long x) {
    const int kWordSize = 16;
    const int kBitMask = 0xFFFF;

    return static_cast<unsigned long long>(precomputed_reverse[x & kBitMask]) << (3 * kWordSize) |
           static_cast<unsigned long long>(precomputed_reverse[(x >> kWordSize) & kBitMask]) << (2 * kWordSize) |
           static_cast<unsigned long long>(precomputed_reverse[(x >> (2 * kWordSize)) & kBitMask]) << (1 * kWordSize) |
           static_cast<unsigned long long>(precomputed_reverse[(x >> (3 * kWordSize)) & kBitMask]);
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                           &ReverseBits, DefaultComparator{}, param_names);
}
