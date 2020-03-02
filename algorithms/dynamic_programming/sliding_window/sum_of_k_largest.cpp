#include <bits/stdc++.h>

using namespace std;

int solution(const vector<int>& arr, int k) {
	int left = 0, len = arr.size(), max_sum = 0, sum = 0;
	
	for (int right = 0; right < len; ++right) {
		if (right - left < k) {
			sum += arr[right];
			max_sum = max(max_sum, sum);
		} else {
			sum -= arr[left++];
			--right;
		}
	}

	return max_sum;
}

int main() {
	const vector<int> arr { 100, 200, 300, 25, 2718, 350 };
	int k;
	cin >> k;
	cout << solution(arr, k) << '\n';

	return 0;
}

