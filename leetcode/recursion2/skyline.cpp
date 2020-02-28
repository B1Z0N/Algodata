#include <bits/stdc++.h>

using namespace std;

#define pb push_back

typedef vector<int> vi;
typedef vector<vi> vvi;

class Solution {
public:
    vvi getSkyline(vvi& buildings) {
        if (buildings.empty()) return {};
        vvi answ = getSkyline(buildings, 0, buildings.size() - 1);
		answ.back()[1] = 0;
		return answ;
    }
    
private:
    
    vvi getSkyline(const vvi& buildings, int l, int r) {
        if (l == r) return {
            {buildings[l][0], buildings[l][2]},
            {buildings[l][1], 0},
        };
        
        int mid = l + (r - l) / 2;
        return merge(getSkyline(buildings, l, mid), 
                     getSkyline(buildings, mid + 1, r));
    }
    
    void append(vvi& res, const vi& st) {
        if (res.empty()) {
            res.pb(st);
            return;
        }
        vi& last = res.back();
        if (last[1] == st[1]) return;
        if (last[0] == st[0]) {
			int left = last[0];
            int maxh = max(last[1], st[1]);
			res.pop_back();
			append(res, {left, maxh}); 
            return;
        }
        
        res.pb(st);
    }
    
    vvi merge(const vvi& fst, const vvi& snd) {
        vvi res;
        int h1 = 0, h2 = 0;
        int i1 = 0, i2 = 0;
        while (i1 < fst.size() && i2 < snd.size()) {
            if (fst[i1][0] <= snd[i2][0]) {
                h1 = fst[i1++][1];
                int maxh = max(h1, h2);
                append(res, {fst[i1 - 1][0], maxh});
            } else {
                h2 = snd[i2++][1];
                int maxh = max(h1, h2);
                append(res, {snd[i2 - 1][0], maxh});
            }
        }
        
        while (i1 < fst.size()) append(res, fst[i1++]);
        while (i2 < snd.size()) append(res, snd[i2++]);
        res.back()[1] = 0; 

        return res;
    }
};


void print(const vvi& res) {
	for (auto& skyline : res) {
			cout << skyline[0] << ' ' << skyline[1] << '\n';
	}
}

int main() {
	Solution sol;
	vvi arr {
		{2, 4, 7}, {2, 4, 5}, {2, 4, 6}	
	};

	print(sol.getSkyline(arr));
	
	return 0;
}
