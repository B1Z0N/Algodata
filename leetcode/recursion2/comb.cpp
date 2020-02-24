#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;

class Solution {
public:
    vvi combine(int n, int k) {
        if (n == 0 || k > n) return {};
        
		vvi res;
       	vi prev;
		
        combine(k, 0, n, res, prev);

        return res;
    }
    
    void combine(int k, int limiter, int n, vvi& res, vi& prev) {
        if (k == 0) {
            res.push_back(prev);
            return;
        }
        
        for (int i = limiter; i < n; ++i) {
            prev.push_back(i + 1);
            combine(k - 1, i + 1, n, res, prev);
            prev.pop_back();
        }
    }
};

void printvv(const vvi& combs) {
	for (auto &comb : combs) {
		for (auto &x : comb) {
			cout << x << ' ';
		}
		cout << '\n';
	}
}

int main() {
	Solution sol;
	int k, n;
	cout << "Enter n and k: ";
	cin >> n >> k;
	printvv(sol.combine(n, k));

	return 0;	
}
