#define pb push_back

class Solution {
public:
    int pivotIndex(const vector<int>& nums) {
        vector<int> sums;
        int sum = 0;
        
        sums.pb(0);
        for (const auto& num : nums) sums.pb(sum += num);
        sums.pb(sum);
        
        for (int i = 1; i < sums.size() - 1; ++i) 
            if (sums[i - 1] == sum - sums[i]) return i - 1; 
        
        return -1;
    }
};
