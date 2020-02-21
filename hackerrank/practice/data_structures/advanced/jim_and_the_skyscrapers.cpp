#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

long long permut2(long long n) {
	return n * (n - 1);	
}

// Complete the solve function below.
long long solve(vector<long long> arr) {
    stack<long long> st;
    st.push(arr[0]);
    long long ans = 0, sequence = 0, cur = 0;

    for (long long i = 1; i < arr.size(); ++i) {
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

    return ans;
}

int  main()
{
#ifdef SUBMISSION
    ofstream fout(getenv("OUTPUT_PATH"));
#endif
    long long arr_count;
    cin >> arr_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<long long> arr(arr_count);

    for (long long arr_itr = 0; arr_itr < arr_count; arr_itr++) {
        long long arr_item = stoi(arr_temp[arr_itr]);

        arr[arr_itr] = arr_item;
    }

    long long result = solve(arr);

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

