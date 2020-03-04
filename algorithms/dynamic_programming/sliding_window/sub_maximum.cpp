#include <bits/stdc++.h>

using namespace std;

vector<int> solution(const vector<int>& arr, int k) {
	vector<int> res;
	deque<int> dq;
	
	for (int i = 0; i < k; ++i) {
		while (!dq.empty() && arr[dq.front()] <= arr[i])
			dq.pop_front();
		dq.push_front(i);
	}

	for (int i = k; i < arr.size(); ++i) {
		res.push_back(arr[dq.back()]);

		while (!dq.empty() && dq.back() <= i - k)
			dq.pop_back();

		while (!dq.empty() && arr[dq.front()] <= arr[i])
			dq.pop_front();

		dq.push_front(i);
	}

	res.push_back(arr[dq.back()]);
	return res;
}

void printv(const vector<int>& arr) {
	for (auto& x : arr) {
		cout << x << ' ';
	}
	cout << '\n';
}

int main() {
	const vector<int> arr { 1, 2, 3, 1, 4, 5, 2, 3, 6 };
	printv(solution(arr, 3));

	return 0;
}
