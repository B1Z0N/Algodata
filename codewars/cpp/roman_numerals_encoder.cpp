#include <bits/stdc++.h>

using namespace std;

string general_roman(char one, char five, char ten, int number) {
	if (number == 0) return {};
	else if (number <= 3) return string(number, one);
  	else if (number <= 5) return string(5 - number, one) + five;
  	else if (number <= 8) return five + string(number - 5, one);
  	else if (number <= 9) return string{one} + ten;

  	return "ERROR";
}


string solution(int number){
	int thousands = number / 1000;
	number -= thousands * 1000;
	int hundreds = number / 100;
	number -= hundreds * 100;
	int tens = number / 10;
  	number -= tens * 10;
  	int digits = number;

	using namespace std::placeholders;
	static auto roman1000 = bind(general_roman, 'M', ' ', ' ', _1);
	static auto roman100 = bind(general_roman, 'C', 'D', 'M', _1);
	static auto roman10 = bind(general_roman, 'X', 'L', 'C', _1);
	static auto roman1 = bind(general_roman, 'I', 'V', 'X', _1);

  	return roman1000(thousands) + roman100(hundreds) + roman10(tens) + roman1(digits);
}


int main() {
	int num;
	cin >> num;
	cout << solution(num) << '\n';
	
	return 0;
}
