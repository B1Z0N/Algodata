#include <cmath>
#include <string>

const int ZERO_ASCII_CODE = 48;

bool narcissistic( int value ){
  auto s {std::to_string(value)};
  int n = s.size(), sum = 0;
  for (const auto& c : s) sum += pow(((int) c) - ZERO_ASCII_CODE, n);
  
  return sum == value;
}
