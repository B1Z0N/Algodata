class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.size() == 1) return nums.front();
        if (nums.front() < nums.back()) return nums.front();
        return nums[findPivot(nums)];
    }
    
private:
    int findPivot(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (nums[m] > nums[r]) l = m + 1;
            else r = m;
        }
        
        return l;
    }
};
