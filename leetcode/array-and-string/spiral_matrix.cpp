#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        int rows = matrix.size(), cols = matrix.front().size();
        int brow = -1, erow = rows, bcol = -1, ecol = cols;
        int row = 0, col = 0, rowadd = 0, coladd = 1;
        vector<int> res;
        
        while (erow - brow > 1 && ecol - bcol > 1) {
            res.push_back(matrix[row][col]);

           	if (rowadd == 1 || rowadd == -1) { 
            	if (row + rowadd == erow) {
              	  rowadd = 0; coladd = -1;
									--ecol;
            	} else if (row + rowadd == brow) {
                	rowadd = 0; coladd = 1;
              		++bcol;
							}
						} else {
								if (col + coladd == ecol) {
                	coladd = 0; rowadd = 1;
                	++brow;
            		} else if (col + coladd == bcol) {
                	coladd = 0; rowadd = -1;
                	--erow;
								}
						}
            
            row += rowadd;
            col += coladd;
        }
        
        return res;
    }
};

void print(const vector<int>& v) {
	for (const auto& x : v) {
		cout << x << ' ';
	}
	cout << '\n';
}

int main() {
	Solution sol;
	vector<vector<int>> v { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	print(sol.spiralOrder(v));

	return 0;
}
