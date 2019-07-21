#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int next_prime( )
// function to compute next prime starting from 2
{
    static auto is_prime { []( int num ) {
        // is num a prime number, made static
        // so that it takes the same memory as 
        // global function, but it's name is hidden
        // in outer function (next_prime)
        for ( int i = 2; i <= std::sqrt( num ); i++)
        {
            if ( num % i == 0 ) return false;
        }

        return true;
    }};

    static int latest = 1;
    latest++;
    while ( !is_prime( latest ) ) latest++;
    // find next prime number

    return latest;
}

/*
 * Complete the waiter function below.
 */
vector<int> waiter(vector<int> A, int q) {
    vector<int> result;
    // resulting array of plates, in order suitable for printing
    vector<int> nextB;
    // array for B[i]
    // we don't need q B-arrays, just one `result` array,
    // in the end of each iteration nextB are pushed to result array
    vector<int> nextA;
    // array denoting A[i], whereas A means A[i - 1]

    while ( q-- )
        // q iterations
    {
        int prime = next_prime();
        // get the i-th prime number

        while ( !A.empty() )
            // while A[i - 1] not empty
        {
            if ( A.back() % prime )
                // if top of the stack is not divisible by i-th prime
                nextA.push_back( A.back() );
            // push it to the A[i]
            else
                // if top of the stack is divisible by i-th prime
                nextB.push_back( A.back() );
            // push it to the B[i]

            A.pop_back();
            // and don't forget to pop it from the top
        }

        while ( !nextB.empty() )
            // then while B[i] not empty
        {
            result.push_back( nextB.back() );
            nextB.pop_back();
            // move it from top of B[i] to `result`
            // in appropriate format, as stated in the
            // problem description
        }

        std::swap( A, nextA );
        // swap A[i-1] (which is empty) with A[i] (which is ready for next iteration)
        // A[i-1] will become A[i] in the next iteration
    }

    // when all iterations are done
    // all B[i] are pushed to `result` array
    // and ready for output
    // there are only A[q] array left to push

    while ( !A.empty() )
        // while A[q] not empty
    {
        result.push_back( A.back() );
        A.pop_back();
        // move it from top of A[q] to result
        // so that result is now ready for printing
        // in appropriate format, as stated in the
        // problem description
    }

    return result;
    // return the whole array
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

    for ( auto val : result )
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