#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> vvi;

struct limits {
    int xstart;
    int xend;
    int ystart;
    int yend;
   
    bool contains(vvi& matrix, int target) {
        int width = matrix[0].size(), height = matrix.size();
		bool start1 = xstart == width ? false : matrix[height - 1][xstart] == target;
		bool start2	= ystart == height ? false : matrix[ystart][width - 1] == target;
		bool end1 = xend == width ? false : matrix[0][xend] == target;
	    bool end2 = yend == height ? false : matrix[yend][0] == target;
		return start1 || start2 || end1 || end2;
    }
};

class Solution {
public:
    bool searchMatrix(vvi& matrix, int target) {
		if (!matrix.size() || !matrix[0].size()) return false;

        auto lims = findLimits(matrix, target);
        if (lims.contains(matrix, target)) return true;
        
        for (int col = lims.xstart; col < lims.xend; ++col) {
			int size = lims.yend - lims.ystart;
            int search = bsearch(target, size, [&](int i){
                return matrix[lims.ystart + i][col];
            });
            if (search < size && matrix[lims.ystart + search][col] == target) return true;
        }
        return false;
    }

private:   
    limits findLimits(vvi& matrix, int target) {
        int width = matrix[0].size(), height = matrix.size();
        
        int xend = bsearch(target, width,  [&](int i){ return matrix[0][i];          });
        int xstart =   bsearch(target, width,  [&](int i){ return matrix[height - 1][i]; });
        int yend = bsearch(target, height, [&](int i){ return matrix[i][0];          });
        int ystart =   bsearch(target, height, [&](int i){ return matrix[i][width - 1];  });
        
        return {xstart, xend, ystart, yend};
    }
    
    template <typename CallableContainer>
    int bsearch(int search, int size, const CallableContainer& arr) {
	    int start = 0, end = size - 1, mid;
	    while (start <= end) { 
		    mid = start + (end - start) / 2;	
		
	    	if (arr(mid) > search) end = mid - 1;
		    else if (arr(mid) < search) start = mid + 1;
		    else return mid;
	    }

	    return start;
    }

};

int main() {
	Solution sol;
	vvi matrix {
			{1, 4, 7, 11, 15},
			{2, 5, 8, 12, 19},
			{3, 6, 9, 16, 22},
			{10, 13, 14, 17, 24},
			{18, 21, 23, 26, 30}
	};
	int a;
	std::cin >> a;
	std::cout << (sol.searchMatrix(matrix, a) ? "Exists\n" : "Don't exist\n");

	return 0;
}
