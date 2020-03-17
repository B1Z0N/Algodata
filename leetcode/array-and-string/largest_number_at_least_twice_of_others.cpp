class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        int *largest = &nums[0], *next_largest = nullptr;
        
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > *largest) {
                next_largest = largest;
                largest = &nums[i];
            } else if (!next_largest || nums[i] > *next_largest) {
                next_largest = &nums[i];
            }
        }
        
        return !next_largest || *largest >= 2 * *next_largest ? largest - nums.data() : -1;
    }
};
