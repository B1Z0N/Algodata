#include <bits/stdc++.h>

using namespace std;

const int ALPHABET_SIZE = 256;

int solution(const string& str, const string& chars) {
	int left = 0, count = 0, shortest = INT_MAX;
	int strlen = str.size();
	int charslen = chars.size();

	int hash_str[ALPHABET_SIZE] = {0};
	int hash_chars[ALPHABET_SIZE] = {0};

	// fulfill 
	for (int i = 0; i < charslen; ++i) hash_chars[chars[i]]++;

	for (int right = 0; right < strlen; ++right) {
		hash_str[str[right]]++;
		if (hash_chars[str[right]] && hash_str[str[right]] <= hash_chars[str[right]]) {
			count++;
		}
		
		if (count == charslen) {	
			while (!hash_chars[str[left]] || hash_str[str[left]] > hash_chars[str[left]]) {
				if (hash_str[str[left]] > hash_chars[str[left]])
					hash_str[str[left]]--;
				++left;
			}
			shortest = min(shortest, right - left + 1);
		}
	}

	return shortest;
}

int main() {
	string chars;
	string str;
	cout << "Enter resulting string: ";
	getline(cin, str);
	cout << "Enter char set to search: ";
	getline(cin, chars);

	cout << "Shortest substring in '" << str << "', containing '" << chars << "' is " \
			<< solution(str, chars) << " characters long\n";

	return 0;
}
