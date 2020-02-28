#include <bits/stdc++.h>

using namespace std;

class Solution {
    std::unordered_map<string, string> codes {
        {"2", "abc"}, 
        {"3", "def"}, 
        {"4", "ghi"}, 
        {"5", "jkl"}, 
        {"6", "mno"}, 
        {"7", "pqrs"}, 
        {"8", "tuv"}, 
        {"9", "wxyz"}
    };
    
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        vector<string> res;
        string current;
        
        letterCombinations(res, digits, current);
        return res;
    }
    
private:
    void letterCombinations(vector<string>& res, string& digits, string& current) {
        if (current.size() == digits.size()) {
            res.push_back(current);
            return;
        }
        
        int i = current.size();
        for (auto& x : codes[string{digits[i]}]) {
            current.push_back(x);
            letterCombinations(res, digits, current);
            current.pop_back();
        }
    }
};

int main() {
	Solution sol;
	sol.letterCombinations("23");

	return 0;
}
