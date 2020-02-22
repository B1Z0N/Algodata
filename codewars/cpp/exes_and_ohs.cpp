#include <bits/stdc++.h>


bool XO(const std::string& str)
{
  int x = 0, o = 0;
  for (const auto& element : str) { 
    x += (int) std::tolower(element) == 'x';
    o += (int) std::tolower(element) == 'o';
  }
  
  return x == o;
}

int main() {
	std::string str;
	std::getline(std::cin, str);
	std::cout << (XO(str) ? "The " : "Not the ") << "same number of 'o's and 'x's\n";

	return 0;
}
