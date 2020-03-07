#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

class MaxRangeTree {
protected:
    static std::vector<int> max_tree(const std::vector<int> vec) {
        int size = vec.size();
        std::vector<int> res (size - 1);
        std::copy(vec.cbegin(), vec.cend(), std::back_inserter(res));
        for (int i = size - 1; i >= 1; --i) 
            res[i - 1] = max(res[left(i) - 1], res[right(i) - 1]);

        return res;
    }
    
    static inline int parent(int i) { return i / 2; }
    static inline int left(int i) { return 2 * i; }
    static inline int right(int i) { return 2 * i + 1; }

    vector<int> tree;
    size_t n;
public:
    MaxRangeTree(const vector<int>& arr) :tree{max_tree(arr)}, n{arr.size()} {}

    // range starting from zero
    int get_max(int a, int b) {
        a += n; b += n;
        int res = INT_MIN;
        while (a <= b) {
            if (a % 2 == 1 /* right */) res = max(res, tree[a++ - 1]);
            if (b % 2 == 0 /* left  */) res = max(res, tree[b-- - 1]);
            
            a = parent(a); b = parent(b);
        }

        return res;
    }
};


// Complete the solve function below.
long solve(vector<int> arr) {
    // O(n)
    MaxRangeTree mrt {arr};
    int n = arr.size();
    long long cnt = 0;
    // O(n^2 * log(n))
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long a = arr[i], b = arr[j], c = mrt.get_max(i, j);
            cnt += a * b <= c;
        }
    }

    return cnt;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int arr_count;
    cin >> arr_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(arr_count);

    for (int i = 0; i < arr_count; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    long result = solve(arr);

    fout << result << "\n";

    fout.close();

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

