#include <bits/stdc++.h>

std::string spinWords(const std::string &s)
{
  auto str = s + ' ';
  auto word_start = str.begin();
  for (auto it = str.begin(); it != str.end(); ++it) {
    if (*it == ' ') {
      if (std::distance(word_start, it) >= 5) {
        std::reverse(word_start, it);
      }
      word_start = it + 1;
    }
  }
  
  str.resize(str.size() - 1);
  return str;
}// spinWords

int main() {
	std::string s;
	std::getline(std::cin, s);
	
	std::cout << spinWords(s) << '\n'; 
	return 0;
}
