class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        if (nums.front() < nums.back()) 
            return bsearch(nums, 0, nums.size() - 1, target);
        
        int pivot = find_pivot(nums);
        
        if (target <= nums.back()) 
            return bsearch(nums, pivot, nums.size() - 1, target);
        else 
            return bsearch(nums, 0, pivot - 1, target);
    }

private:
    int bsearch(vector<int>& nums, int l, int r, int target) {
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] == target) return m;
            else if (nums[m] > target) r = m - 1;
            else l = m + 1;
        }
        
        return -1;
    }
    
    int find_pivot(vector<int>& nums) {        
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (nums[m] > nums[r]) l = m + 1;
            else r = m;
        }
        
        return l;
    }
    
    
};
