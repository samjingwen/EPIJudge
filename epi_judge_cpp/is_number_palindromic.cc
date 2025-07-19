#include <cmath>

#include "test_framework/generic_test.h"

bool IsPalindromeNumber(int x) {
  if (x < 0) {
    return false;
  }

  int size = std::floor(std::log10(x)) + 1;
  int msd_mask = static_cast<int>(std::pow(10, size - 1));

  for (int i = 0; i < size / 2; ++i) {
    int msd = x / msd_mask;
    int lsd = x % 10;

    if (msd != lsd) {
      return false;
    }

    x %= msd_mask;
    x /= 10;
    msd_mask /= 100;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
