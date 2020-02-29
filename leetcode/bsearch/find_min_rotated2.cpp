    class Solution {
    public:
        int findMin(vector<int>& nums) {
            if (nums.size() == 1) return nums.front();
            if (nums.front() < nums.back()) return nums.front();
            return nums[findPivot(nums)];
        }

    private:
        inline int bunknown(const vector<int>&nums, int l, int m, int r) {
            return nums[m] == nums[l] && nums[m] == nums[r];
        }
        int findPivot(vector<int>& nums) {
            int l = 0, r = nums.size() - 1;
            while (l < r) {
                int m = (l + r) / 2;
                if (bunknown(nums, l, m, r)) {
                    int origl = l, origr = r;
                    do {
                        ++l;
                        --r;
                        if (r == origl || l == origr) return r;
                    } while(bunknown(nums, l, m, r));
                } else {
                    if (nums[m] > nums[r]) l = m + 1;
                    else r = m;
                }
            }

            return l;
        }
    };
