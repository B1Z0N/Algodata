#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct build
{
    int index;
    int height;
};

// Complete the largestRectangle function below.
long largestRectangle(vector<int> h) {
    long space {};
    h.push_back(0);
    stack<build> st;
    st.push( { 0 , h[0] } );

    for( int i = 1; i < h.size(); i++ )
    {
        while( !st.empty() && h[i] < st.top().height)
        {
            int height = st.top().height;
            st.pop();
            if (st.empty()) break;
            int index = st.empty() ? 0 : st.top().index;
            long new_space = height * ( i - index - 1);
            space = std::max( space,  new_space );
        }

        st.push( { i, h[i] });
    }

    return space;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    // int n;
    // cin >> n;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // string h_temp_temp;
    // getline(cin, h_temp_temp);

    // vector<string> h_temp = split_string(h_temp_temp);

    // vector<int> h(n);

    // for (int i = 0; i < n; i++) {
    //     int h_item = stoi(h_temp[i]);

    //     h[i] = h_item;
    // }

    long result = largestRectangle( { 1, 2, 3, 4, 5 } );

    cout << result << "\n";

    // fout.close();

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
