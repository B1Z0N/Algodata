#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct Index
{
    long long val;
    long long index;
};

long long calcIndex(stack<Index> &st, vector<long long> &arr, long long i)
{
    if (!st.empty() && arr[i] > st.top().val)
    {
        long long current = st.top().val, left, right, res = 0;
        st.pop();
        if (st.empty())
            return 0;
        if (st.top().val == current) {
            res = calcIndex(st, arr, i);
            left = st.top().index;
        } else {
            left = st.top().index;
            res = calcIndex(st, arr, i);
        }
        right = i + 1;
        return max(left * right, res);
    }

    return 0;
}

// Complete the solve function below.
long long solve(vector<long long> arr)
{
    stack<Index> st{};
    st.push(Index{arr[0], 1});
    long long res = 0;
    for (long long i = 1; i < arr.size(); ++i)
    {
        res = max(res, calcIndex(st, arr, i));
        st.push(Index{arr[i], i + 1});
        cout << st.size() << '\n';
    }

    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    long long arr_count;
    cin >> arr_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<long long> arr(arr_count);

    for (long long arr_itr = 0; arr_itr < arr_count; arr_itr++)
    {
        long long arr_item = stoi(arr_temp[arr_itr]);

        arr[arr_itr] = arr_item;
    }

    long long result = solve(arr);

    fout << result << "\n";
    cout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string)
{
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ')
    {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos)
    {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
