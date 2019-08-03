#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);


//------------------------------------------------------------------------------------------
// @Problem
// You are given a square grid with some cells open (.) and some blocked (X). 
// Your playing piece can move along any row or column until it reaches the edge 
// of the grid or a blocked cell. Given a grid, a start and an end position, determine 
// the number of moves it will take to get to the end position.
// 
// @Example
// For example, you are given a grid with sides n = 3 described as follows:
//
//                  ...
//                  .X.
//                  ...
//
// Your starting position ( startX, startY ) = ( 0, 0 ) 
// so you start in the top left corner. The ending position is 
// (  goalX,  goalY ) = ( 1, 2 ) The path is ( 0, 0 ) -> ( 0, 2 ) -> ( 1, 2 )
// It takes 2 moves to get to the goal.
//
// @Input format
// 3
// ...
// .X.
// ...
// 0 0 1 2
//
// @Output
// 2
//
//--------------------------------------------------------------------------------------------



// Complete the minimumMoves function below.
int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    queue<pair<int, int>> q;
    q.push( { startX, startY } );
    queue<int> dist;
    dist.push(0);
    char mark = 'X';
    int steps {};
    int xsize = grid.size();
    int ysize = grid[0].size();

    const pair<int, int> mv[] = {  {-1, 0 }, { 0, +1 }, { 1, 0 }, { 0, -1 } };

    while( !q.empty() )
    {
        if( q.front().first == goalX && q.front().second == goalY )
            return dist.front();

        for( int i = 0; i < 4; i++ )
        {
            int newX = q.front().first  + mv[i].first ;
            int newY = q.front().second + mv[i].second;
            while( newX < xsize && newX >= 0 && newY < ysize && newY >= 0  &&
                   grid[newX][newY] != mark    )
            {
                q.push( { newX, newY } );
                dist.push( dist.front() + 1 );

                grid[newX][newY] = mark;

                newX += mv[i].first ;
                newY += mv[i].second;
            }
        }

        q.pop();
        dist.pop();
    } 

    return -1;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string startXStartY_temp;
    getline(cin, startXStartY_temp);

    vector<string> startXStartY = split_string(startXStartY_temp);

    int startX = stoi(startXStartY[0]);

    int startY = stoi(startXStartY[1]);

    int goalX = stoi(startXStartY[2]);

    int goalY = stoi(startXStartY[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

    cout << result << "\n";

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
