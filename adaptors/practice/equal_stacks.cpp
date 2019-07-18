#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

using istack = stack<int>;

int __equalStacks( 
    istack& h1, istack& h2, istack& h3,
    int full1, int full2, int full3
    )
{    
    while( !h1.empty() && !h2.empty() && !h3.empty() )
    {
        if( full1 == full2 && full2 == full3)
            return full1;

        if( full1 >= full2 && full1 >= full3 )
        {
            full1 -= h1.top();
            h1.pop();
        }
        else if( full2 >= full3 && full2 >= full1 )
        {
            full2 -= h2.top();
            h2.pop();
        }
        else if( full3 >= full2 && full3 >= full1 )
        {
            full3 -= h3.top();
            h3.pop();
        }
    }

    return 0;
}

void init_stack( istack& st, const vector<int>& v )
{
    for( int i = v.size() - 1; i >= 0; i-- )
        st.push( v[i] );
}

int equalStacks(vector<int> h1, vector<int> h2, vector<int> h3) 
{
    int full1 { accumulate(begin(h1), end(h1), 0) };
    int full2 { accumulate(begin(h2), end(h2), 0) };
    int full3 { accumulate(begin(h3), end(h3), 0) };

    istack st1; init_stack( st1, h1);
    istack st2; init_stack( st2, h2);
    istack st3; init_stack( st3, h3);

    cout << st1.top() << st2.top() << st3.top(); 

    return __equalStacks( st1, st2, st3, full1, full2, full3 );
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n1N2N3_temp;
    getline(cin, n1N2N3_temp);

    vector<string> n1N2N3 = split_string(n1N2N3_temp);

    int n1 = stoi(n1N2N3[0]);

    int n2 = stoi(n1N2N3[1]);

    int n3 = stoi(n1N2N3[2]);

    string h1_temp_temp;
    getline(cin, h1_temp_temp);

    vector<string> h1_temp = split_string(h1_temp_temp);

    vector<int> h1(n1);

    for (int h1_itr = 0; h1_itr < n1; h1_itr++) {
        int h1_item = stoi(h1_temp[h1_itr]);

        h1[h1_itr] = h1_item;
    }

    string h2_temp_temp;
    getline(cin, h2_temp_temp);

    vector<string> h2_temp = split_string(h2_temp_temp);

    vector<int> h2(n2);

    for (int h2_itr = 0; h2_itr < n2; h2_itr++) {
        int h2_item = stoi(h2_temp[h2_itr]);

        h2[h2_itr] = h2_item;
    }

    string h3_temp_temp;
    getline(cin, h3_temp_temp);

    vector<string> h3_temp = split_string(h3_temp_temp);

    vector<int> h3(n3);

    for (int h3_itr = 0; h3_itr < n3; h3_itr++) {
        int h3_item = stoi(h3_temp[h3_itr]);

        h3[h3_itr] = h3_item;
    }

    int result = equalStacks(h1, h2, h3);

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
