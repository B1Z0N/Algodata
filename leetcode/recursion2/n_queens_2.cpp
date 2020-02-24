#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

class Solution {
public:
    int totalNQueens(int n) {
        if (n == 0 || n == 1) return n;
        vvi board(n, vi(n, 0));
        int ans = totalNQueens(0, board);
        return ans;
    }
    
private:
    
    void print(vvi& board) {
        for (auto& row : board) {
            for (auto& x : row) {
                cout << x << ' ';
            }
            cout << '\n';
        }
    }
    
    int totalNQueens(int y, vvi& board) {
        int n = board.size(), count = 0;
        if (y == n - 1) 
			return std::count(board[y].begin(), board[y].end(), 0);
        
        for (int x = 0; x < n; ++x) {
            if (!board[y][x]) {
                queenTo(x, y, board, true);
                count += totalNQueens(y + 1, board);
                queenTo(x, y, board, false);
            }
        }
        
        return count;
    }
    
    void queenTo(int x, int y, vvi& board, bool occupy) {
        int n = board.size();
        // diagonal
		for (int i = x, j = y; i >= 0 && j >= 0; --i, --j) occupy ? ++board[j][i] : --board[j][i];
        for (int i = x, j = y; i < n && j < n; ++i, ++j)   occupy ? ++board[j][i] : --board[j][i];
        for (int i = x, j = y; i >= 0 && j < n; --i, ++j)  occupy ? ++board[j][i] : --board[j][i];
        for (int i = x, j = y; i < n && j >= 0; ++i, --j)  occupy ? ++board[j][i] : --board[j][i];
	
		// vertical
		for (int i = 0; i < n; ++i) occupy ? ++board[i][x] : --board[i][x];

		// horizontal
		for (int j = 0; j < n; ++j) occupy ? ++board[y][j] : --board[y][j];
	}
};


int main() {
	Solution sol;
	int n;
	cin >> n;
	cout << sol.totalNQueens(n) << '\n';	
}
