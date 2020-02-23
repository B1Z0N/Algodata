class Solution {
public:
    void reverseString(vector<char>& s, int i = 0) {
        int len = s.size();
        if (i == len / 2) return;
        std::swap(s[i], s[len - i - 1]);
        reverseString(s, i + 1);
    }
};
