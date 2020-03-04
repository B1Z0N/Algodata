#include <bits/stdc++.h>

using namespace std;

vector<double> solution(const vector<int>& arr, int k) {
    vector<double> res;
    if (k == 1) {
    	copy(arr.begin(), arr.end(), back_inserter(res));
    	return res;
    }
        
	multiset<int> ms;

	for (int i = 0; i < k - 1; ++i) ms.insert(arr[i]);
	
	for (int i = k - 1; i < arr.size(); ++i) {
		ms.insert(arr[i]);

		auto it = next(ms.begin(), k / 2 - 1);
		res.push_back(
    	// 0.5 for overflow prevention
    	k % 2 ? *next(it) : (0.5 * *it) + (0.5 * *next(it))
    	);

		ms.erase(ms.lower_bound(arr[i - k + 1]));	
	}	

	return res;
}

void printv(const vector<double>& vec) {
	for (const auto& x : vec) cout << x << ' ';
	cout << '\n';
}

int main() {
	const vector<int> arr {-1, 5, 13, 8, 2, 3, 3, 1};	
	printv(solution(arr, 3));
	printv(solution(arr, 4));

	return 0;
}
