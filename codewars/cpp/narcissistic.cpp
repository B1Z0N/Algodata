#include <cmath>

bool narcissistic( int value ){
  int len = std::log10(value) + 1, n = value, sum = 0;
  
  while (n) {
    sum += std::pow(n % 10, len);
    n /= 10;
  }
  
  return sum == value;
}
