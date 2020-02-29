#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(const vector<int>& numbers, int target) {
		if (numbers.size() == 2) return {1, 2};
        int r = bsearch(numbers, 0, numbers.size() - 1, target - 1);
        int l = bsearch(numbers, 0, r, target / 2);
        
        for (int i = r; i >= l; --i) {
			if (numbers[i] + numbers.front() > target) continue;
            int j = bsearch(numbers, 0, i, target - numbers[i]);

            if (numbers[j] + numbers[i] == target) return {j + 1, i + 1};
        }

		return {};
    }
    
private:
    int bsearch(const vector<int>& nums, int l, int r, int target) {
	if (nums[r] < target) return r;
        while (l < r) {
            int m = (r + l) / 2;
            if (nums[m] < target) l = m + 1;
            else r = m;
        }
        
        return l;
    }
};

void test_two_sum(const std::vector<int>& arr) {
	for (const auto& x : arr) std::cout << x << ' ';
	std::cout << "\n\n";
	Solution sol;

	for (const auto& x : arr) {
		for (const auto& y : arr) {
			if (x == y) continue;
			auto res = sol.twoSum(arr, x + y);
			std::cout << "For " << x + y << " = [" << res[0]  << ' ' << res[1] << "]\n";
			if (arr[res[0] - 1] + arr[res[1] - 1] != x + y) std::cout << "Error up!\n";
		}
	}
}

int main() {
	test_two_sum({1, 2, 3, 9, 21});

	return 0;
}
