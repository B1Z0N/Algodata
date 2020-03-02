#include <bits/stdc++.h>

using namespace std;

// the longest sequence of 1s 
// if we are allowed to flip k 0s
int flips(vector<bool> bits, int k) {
	int zeros = 0, sequence = 0, left = 0, right = 0;
	while (right < bits.size()) {
		if (zeros <= k) {
			!bits[right] && ++zeros;
			++right;
		}

		if (zeros > k) {
			!bits[left] && --zeros;
			++left;
		}

		sequence = max(sequence, right - left);	
	}

	return sequence;
}

int main() {
	vector<bool> bits { 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1 };
	cout << flips(bits, 3) << '\n';	

	return 0;
}
