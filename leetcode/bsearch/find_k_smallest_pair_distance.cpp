class Solution1 {
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

class Solution2 {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        int l = 0, r = nums[n - 1] - nums[0];
        while (l < r) {
            int m = (l + r) / 2;
            if (possible(m, k, nums)) r = m;
            else l = m + 1;
        }

        return l;
    }

private:
    // is there number of pairs >= `k`
    // with distance <= `guess`
    bool possible(int guess, int k, const vector<int>& nums) {
        int count = 0, left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            while (nums[right] - nums[left] > guess) ++left;
            count += right - left;
        }

        return count >= k;
    }
};
