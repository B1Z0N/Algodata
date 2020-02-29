class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num == 0 || num == 1) return true;
        
        int l = 1, r = num / 2;
        while (l < r) {
            int m = (l + r) / 2;
            if (m < num / m) l = m + 1;
            else r = m;
        }
        
        return (double) l == (double) num / l;
    }
};
