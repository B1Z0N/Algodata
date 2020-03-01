class Solution1 {
public:
    int findDuplicate(vector<int>& nums) {
        std::unordered_multiset counter {nums.begin(), nums.end()};
        for (const auto& x : nums)
            if (counter.count(x) > 1) return x;
        
        return -1;
    }
};

class Solution2 {
public:
    int findDuplicate(vector<int>& nums) {
        int hare = 0, tortoise = 0;
        do {
            hare = nums[nums[hare]];
            tortoise = nums[tortoise];
        } while (nums[hare] != nums[tortoise]);

        hare = 0;
        while (nums[hare] != nums[tortoise]) {
            hare = nums[hare];
            tortoise = nums[tortoise];
        }

        return nums[hare];
    }
};
