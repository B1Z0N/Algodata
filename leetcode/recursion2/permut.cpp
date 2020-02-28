class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.empty()) return {};
        if (nums.size() == 1) return {nums};
        
        vector<vector<int>> res;
        vector<int> current;
        vector<bool> including {nums.size(), true};
        
        permute(res, nums, including, current);
        return res;
    }

private:
    void permute(vector<vector<int>>& res, vector<int>& nums, 
                 vector<bool>& including, vector<int>& current) {
        if (current.size() == nums.size()) {
            res.push_back(current);
            return;
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            if (including[i]) {
                including[i] = false;
                current.push_back(nums[i]);
                permute(res, nums, including, current);
                current.pop_back();
                including[i] = true;
            }
        }
    }
};
