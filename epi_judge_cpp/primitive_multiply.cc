#include "test_framework/generic_test.h"

typedef unsigned long long ull;

ull Add(ull a, ull b) {
    ull sum = 0, carryin = 0, k = 1, temp_a = a, temp_b = b;
    while (temp_a || temp_b) {
        ull ak = a & k, bk = b & k;
        ull carryout = (ak & bk) | (ak & carryin) | (bk & carryin);
        sum |= (ak ^ bk ^ carryin);
        carryin = (carryout << 1), temp_a >>= 1, temp_b >>= 1, k <<= 1;
    }
    return sum | carryin;
}

ull Multiply(ull x, ull y) {
    ull sum = 0;
    while (x) {
        if (x & 1) {
            sum = Add(sum, y);
        }
        x >>= 1, y <<= 1;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x", "y"};
    return GenericTestMain(args, "primitive_multiply.cc",
                           "primitive_multiply.tsv", &Multiply,
                           DefaultComparator{}, param_names);
}
