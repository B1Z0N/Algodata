typedef long long ll;

class Solution {
public:
    double myPow(double x, ll n) {
        return n < 0 ? 1 / __myPow(x, -n) : __myPow(x, n);
    }
    
    double __myPow(double x, ll n) {
        if (n == 0 || x == 1) return 1;
        
        if (n % 2 == 0) {
            double m = __myPow(x, n / 2);
            return m * m;
        } else return x * myPow(x, n - 1);
    }
};
