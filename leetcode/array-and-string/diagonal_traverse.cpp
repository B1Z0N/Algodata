typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

#define pb push_back

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) {
            return {};
        }
        
        int m = matrix.size(), n = matrix[0].size();
        
        vector<int> res(m*n);
        int row = 0, col = 0;
        bool isUp = true;
        
        int indx = 0;
        do {
            res[indx++] = matrix[row][col];
            tie(row, col) = getNext(row, col, m, n, isUp);
        } while (row < m && col < n);
        
        return res;
    }
    
    pair<int, int> getNext(int row, int col, int m, int n, bool& isUp) {
        int newRow = isUp ? row-1 : row+1, newCol = isUp ? col+1 : col-1;
        if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n) {
            if ((col == 0 && row+1 < m && !isUp) || (col+1 == n && isUp)) {
                isUp = !isUp;
                return {row+1, col};
            } else {
                isUp = !isUp;
                return {row, col+1}; 
            }
        }
        
        return {newRow, newCol};
    }
};
