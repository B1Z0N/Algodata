// Solution for two arrays(like in problem statement)
class Solution {
    inline bool between(const int a1, const int b, const int a2) { return a1 <= b && b <= a2; }
    
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if ((nums1.size() + nums2.size()) % 2 == 1) {
            return findKthInTwoSortedArrays(nums1, nums2, (nums1.size() + nums2.size()) / 2 + 1);
        } else {
            return (findKthInTwoSortedArrays(nums1, nums2, (nums1.size() + nums2.size()) / 2) +
                    findKthInTwoSortedArrays(nums1, nums2, (nums1.size() + nums2.size()) / 2 + 1)) / 2.0;
        }
    }
    
private:
    int findKthInTwoSortedArrays(const vector<int>& nums1, const vector<int>& nums2, int k) {
        const int n = nums1.size();
        const int m = nums2.size();
        
        if (n > m) return findKthInTwoSortedArrays(nums2, nums1, k);
        
        int left = 0, right = n;
        while (left < right) {
            const int mid1 = left + (right - left) / 2, mid2 = k - mid1 - 1;
            if (between(0, mid2, m - 1) && nums1[mid1] >= nums2[mid2]) right = mid1;
            else left = mid1 + 1;
        }
        
        int a = left > 0 ? nums1[left - 1] : INT_MIN;
        int b = k - left - 1 >= 0 ? nums2[k - left - 1] : INT_MIN;
        
        return max(a, b);
    }
};

class GenericSolution {
public:
    double findMedianSortedArrays(const vector<vector<int>>& arrs) {
	    auto size = accumulate(arrs.begin(), arrs.end(), 0, [](int prev, const vector<int>& arr) { return prev + arr.size(); });
	    if (size % 2 == 1) {
            return findKthInSortedArrays(arrs, size / 2 + 1);
        } else {
            return (findKthInSortedArrays(arrs, size / 2) +
					findKthInSortedArrays(arrs, size / 2 + 1)) / 2.0;
        }
    }

	int findKthInSortedArrays(const vector<vector<int>>& arrs, int k) {
		int left = numeric_limits<int>::max();
		int right = numeric_limits<int>::min();
		for (const auto& arr : arrs) {
			if (!arr.empty() && arr.front() < left) left = arr.front();
			if (!arr.empty() && arr.back() > right) right = arr.back();
		}

		while (left <= right) {
			const int mid = left + (right - left) / 2;
			if (match(arrs, mid, k)) right = mid - 1;
			else left = mid + 1;
		}

		return left;
    }

	bool match(const vector<vector<int>>& arrs, int num, int target) {
		int res = 0;
		for (const auto& arr : arrs) {
			if (!arr.empty())
				res += distance(
					arr.cbegin(),
				   	upper_bound(arr.cbegin(), arr.cend(), num)
				);
        }

		return res >= target;
	}
};

