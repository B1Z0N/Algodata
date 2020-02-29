#define POW(x) ((x) * (x))

class Solution {
public:
    int mySqrt(long long x) {
        if (x < 2) return x;
        
        int l = 1, r = x / 2;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (mid > x / mid) r = mid - 1;
            else l = mid + 1;
        }
        
        return l - 1;
    }
};
