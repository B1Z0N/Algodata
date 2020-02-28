class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        return search(nums, 0, nums.size() - 1, target);
    }
    
private:
    
    int search(vector<int>& nums, int start, int end, int target) {
        if (start == end) return nums[start] == target ? start : -1;
        
        int mid = start + (end - start) / 2;
        if (nums[mid] >= target) return search(nums, start, mid, target);
        else return search(nums, mid + 1, end, target);
    }
};
