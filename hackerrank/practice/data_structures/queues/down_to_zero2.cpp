#include <bits/stdc++.h>

using namespace std;

int divisor(int n) {
	int i = (int) sqrt(n);
	while (i != 1) 
		if (n % i == 0) return i;
	return 1; 
}

/*
 * Complete the downToZero function below.
 */
int downToZero(int n) {
    /*
     * Write your code here.
     */
	int i = 0;
	while (n) {
		int div = divisor(n);
		if (div == 1) --n;
		else n /= div;
		++i;
	}

	return i;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int result = downToZero(n);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

