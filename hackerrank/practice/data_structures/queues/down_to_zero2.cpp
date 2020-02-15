#include <bits/stdc++.h>

using namespace std;

const int NUMS_SIZE = 1e6 + 1;

int main()
{
	int nums[NUMS_SIZE];
	nums[0] = 0, nums[1] = 1, nums[2] = 2, nums[3] = 3;
	for (int i = 4; i < NUMS_SIZE; ++i) nums[i] = -1;

	for (int i = 0; i < NUMS_SIZE; ++i) {
			if (nums[i] == -1 || nums[i] > (nums[i - 1] + 1)) 
					nums[i]  = nums[i - 1] + 1;
			for (int j = 1; j <= i && j * i < NUMS_SIZE; ++j) {
				if (nums[j * i] == -1 || nums[j * i] > nums[i] + 1)
					nums[j * i] = nums[i] + 1;
			}
	}

    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int result = nums[n];

        fout << result << "\n";
        cout << result << "\n";
    }

    fout.close();

    return 0;
}

