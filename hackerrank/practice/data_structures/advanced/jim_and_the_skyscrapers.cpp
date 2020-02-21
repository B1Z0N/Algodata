#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

typedef pair<int, int> pii;

int fact(int n) {
    return n == 0 ? 1 : fact(n - 1) * n;
}

int permut2(int n) {
    int fact_n_2 = fact(n - 2);
    return (fact_n_2 * n * (n - 1))/ (2 * fact_n_2);
}

// Complete the solve function below.
int solve(vector<int> arr) {
    stack<int> st;
    st.push(arr[0]);
    int ans = 0, sequence = 0, cur = 0;

    for (int i = 1; i < arr.size(); ++i) {
        while (!st.empty() && arr[i] > st.top()) {
            cur = st.top();
            while (!st.empty() && st.top() == cur) {
                st.pop();
                ++sequence;
            }
            if (sequence > 1) ans += permut2(sequence);
            sequence = 0;
        }
        st.push(arr[i]);
    }

    while (!st.empty()) {
        cur = st.top();
        while (!st.empty() && st.top() == cur) {
            st.pop();
            ++sequence;
        }
        if (sequence > 1) ans += permut2(sequence);
		sequence = 0;
    }

    return ans << 1;
}

int main()
{
#ifdef SUBMISSION
    ofstream fout(getenv("OUTPUT_PATH"));
#endif
    int arr_count;
    cin >> arr_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(arr_count);

    for (int arr_itr = 0; arr_itr < arr_count; arr_itr++) {
        int arr_item = stoi(arr_temp[arr_itr]);

        arr[arr_itr] = arr_item;
    }

    int result = solve(arr);

#ifdef SUBMISSION
    fout << result << "\n";

    fout.close();
#else
	cout << result << '\n';
#endif

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

