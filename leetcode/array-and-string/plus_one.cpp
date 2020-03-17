class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        bool addition = true;
        for (int i = n - 1; i >= 0; --i) {
            if (!addition) return digits;
            
            if (digits[i] == 9) {
                digits[i] = 0;
            } else {
                ++digits[i];
                addition = false;
            }
        }
        
        if (addition) {
            digits[0] = 1;
            digits.push_back(0);
        }
        
        return digits;
    }
};
