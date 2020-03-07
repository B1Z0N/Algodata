#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

typedef vector<int>::iterator vit;

long solve(vector<int>& arr,  const vit& l, const vit& r) {
	if (distance(l, r) <= 1) return 0;
	vit maxel {max_element(l, r)};
	long answ = solve(arr, l, maxel) + solve(arr, next(maxel), r);
	
	// calculate pairs on each of subarrays
	// assuming maxel is maximal element
	for (auto itl = l; itl != maxel; ++itl) {
		for (auto itr = next(maxel); itr != r; ++itr) {
			long long a = *itl, b = *itr;
			if (a * b <= *maxel) ++answ;
			else break;		
		}
	}

	// calculate the number of pairs that include maxel
	for (auto itone = l; *itone == 1 && itone != maxel; ++itone) ++answ;
	for (auto itone = next(maxel); *itone == 1 && itone != r; ++itone) ++answ;

	inplace_merge(l, next(maxel), r);
	return answ;
}
// Complete the solve function below.
long solve(vector<int> arr) {
	return solve(arr, arr.begin(), arr.end());
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
    cout << result << "\n";

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

