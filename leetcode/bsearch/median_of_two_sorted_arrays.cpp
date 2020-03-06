
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
