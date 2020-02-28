class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if (heights.empty()) return {};
        
        stack<int> st;
        heights.push_back(0);
        int len = heights.size();
        st.push(len - 1);
        int square = 0;
        
        for (int i = len - 2; i >= 0; --i) {
            while (heights[st.top()] > heights[i]) {
                int cursq = heights[st.top()];
                st.pop();
                cursq *= st.top() - i - 1;
                if (cursq > square) square = cursq;
            }
            st.push(i);
        }
        
        while (st.size() > 1) {
            int cursq = heights[st.top()];
            st.pop();
            cursq *= st.top();
            if (cursq > square) square = cursq;
        }
        
        heights.pop_back();
        return square;        
    }
};
