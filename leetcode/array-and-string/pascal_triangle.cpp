#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows == 0) return {};
        
        vector<vector<int>> res { {1} };
        generate(res, numRows - 1);
        return res;
    }
    
    void generate(vector<vector<int>>& res, int k) {
        if (k == 0) return;
        
        vector<int> &prev = res.back(), cur;
        cur.push_back(1);
        for (int i = 0; i < prev.size() - 1; ++i) cur.push_back(prev[i] + prev[i + 1]);
        cur.push_back(1);
        
        res.push_back(std::move(cur));
        generate(res, k - 1);
    }
};

int main() {
	int n;
	cin >> n;
	Solution sol;
	sol.generate(n);

	return 0;
}
