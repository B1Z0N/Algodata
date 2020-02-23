#include <iostream>
#include <vector>
using namespace std;

int bsearch(const vector<int>& arr, int search) {
	int start = 0, end = arr.size() - 1, mid;
	while (start <= end) { 
		mid = start + (end - start) / 2;	
		
		if (arr[mid] > search) end = mid - 1;
		else if (arr[mid] < search) start = mid + 1;
		else return mid;
	}

	return start;
}

void bsearch_test(const vector<int>& arr) {
	for (int i = 0; i < arr.size(); ++i) {
		cout << "Searching for " << arr[i];
		cout << " (" << i << "th index): " << bsearch(arr, arr[i]);
		cout << '\n';
	}
}

int main() {
	vector<int> arr {1, 3, 9, 22, 58, 92, 222};
	cout << bsearch(arr, 10) << '\n';
	cout << bsearch(arr, -29) << '\n';
	cout << bsearch(arr, 60) << '\n';
	cout << bsearch(arr, 329) << '\n';
	return 0;
}
