class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        vector<int> dists;
        for (int i = 0; i < nums.size() - 1; ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                dists.push_back(abs(nums[i] - nums[j]));
            }
        }
        
        std::sort(dists.begin(), dists.end());
        return dists[k - 1];
    }
};
