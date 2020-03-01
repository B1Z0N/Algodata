class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        std::unordered_multiset counter {nums.begin(), nums.end()};
        for (const auto& x : nums)
            if (counter.count(x) > 1) return x;
        
        return -1;
    }
};
