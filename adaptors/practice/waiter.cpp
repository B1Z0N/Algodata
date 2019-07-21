#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int next_prime( )
{
    static auto is_prime { []( int num ) {
        for( int i = 2; i <= std::sqrt( num ); i++)
        {
            if( num % i == 0 ) return false;
        }

        return true;
    }};

    static int latest = 1;
    latest++;
    while( !is_prime( latest ) ) latest++;

    cout << latest << " ";
    return latest;
}

/*
 * Complete the waiter function below.
 */
vector<int> waiter(vector<int> A, int q) {
    vector<int> result;
    vector<int> nextB;
    vector<int> nextA;

    while( q-- )
    {
        int prime = next_prime();

        while( !A.empty() )
        {
            if( A.back() % prime )
                nextA.push_back( A.back() );
            else
            {
                nextB.push_back( A.back() );
            }

            A.pop_back();
        }

        while( !nextB.empty() )
        {
            result.push_back( nextB.back() );
            nextB.pop_back();
        }

        std::swap( A, nextA );
    }

    while( !A.empty() )
    {
        result.push_back( A.back() );
        A.pop_back();
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nq_temp;
    getline(cin, nq_temp);

    vector<string> nq = split_string(nq_temp);

    int n = stoi(nq[0]);

    int q = stoi(nq[1]);

    string number_temp_temp;
    getline(cin, number_temp_temp);

    vector<string> number_temp = split_string(number_temp_temp);

    vector<int> number(n);

    for (int number_itr = 0; number_itr < n; number_itr++) {
        int number_item = stoi(number_temp[number_itr]);

        number[number_itr] = number_item;
    }

    vector<int> result = waiter(number, q);

    for( auto val : result )
    {
        fout << val << "\n";
    }

    fout << "\n";

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