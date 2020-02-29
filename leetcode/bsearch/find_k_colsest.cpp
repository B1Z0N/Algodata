class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res;
        int i = bsearch(arr, x);
        int i1 = i - 1, i2 = i;
        while (i2 < arr.size() && i1 >= 0 && k-- > 0)
            abs(arr[i1] - x) <= abs(arr[i2] - x) ? --i1 : ++i2;
        
        while (i1 >= 0 && k-- > 0) i1--;
        while (i2 < arr.size() && k-- > 0) i2++;
        
        for (int i = i1 + 1; i < i2; ++i) res.push_back(arr[i]);
        
        return res;
    }
    
private:
    int bsearch(vector<int>& arr, int target) {
        if (arr.back() < target) return arr.size();
        
        int l = 0, r = arr.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (arr[m] < target) l = m + 1;
            else r = m;
        }
        
        return l;
    }
};
