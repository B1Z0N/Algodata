class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int i = bsearch(letters, target + 1);
        return letters[i];
    }
    
private:
    int bsearch(vector<char>& letters, char target) {
        if (letters.back() < target) return 0;
        
        int l = 0, r = letters.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (letters[m] < target) l = m + 1;
            else r = m;
        }
        
        return l;
    }
};
