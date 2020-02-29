class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) 
            return intersection(nums2, nums1);
        
        unordered_set<int> set1 {nums1.cbegin(), nums1.cend()};
        vector<int> res;
        
        for (const auto& x : nums2) {
            if (set1.find(x) != set1.end()) {
                res.push_back(x);
                set1.erase(x);
            }
        }
        
        return res;
    }
};
