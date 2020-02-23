class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex == 0) return {1};
        vector<int> current{1, 1};
        if (rowIndex == 1) return current;
        return getRow(current, rowIndex - 2);
        
    }
    
    vector<int> getRow(vector<int>& current, int rowIndex) {
        vector<int> next {1};
        int prev = 1;
        std::for_each(++current.begin(), current.end(), [&](int cur) {
            next.push_back(prev + cur);
            prev = cur;
        });
        next.push_back(1);
        
        return rowIndex == 0 ? next : getRow(next, rowIndex - 1);
    }
};
