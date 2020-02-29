class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) 
            return intersect(nums2, nums1);
        
        unordered_multiset<int> set1 {nums1.cbegin(), nums1.cend()};
        vector<int> res;
        
        for (const auto& x : nums2) {
            auto it = set1.find(x);
            if (it != set1.end()) {
                res.push_back(x);
                set1.erase(it);
            }
        }
        
        return res;
    }
};
