#include <bits/stdc++.h>

using namespace std;

class MaxRangeTree {
protected:
	static std::vector<int> max_tree(const std::vector<int> vec) {
    	int size = vec.size();
    	std::vector<int> res (size - 1);
    	std::copy(vec.cbegin(), vec.cend(), std::back_inserter(res));
    	for (int i = size - 1; i >= 1; --i) 
			res[i - 1] = max(res[left(i) - 1], res[right(i) - 1]);

    	return res;
	}
	
	static inline int parent(int i) { return i / 2; }
	static inline int left(int i) { return 2 * i; }
	static inline int right(int i) { return 2 * i + 1; }

	vector<int> tree;
	size_t n;
public:
	MaxRangeTree(const vector<int>& arr) :tree{max_tree(arr)}, n{arr.size()} {}

	// range starting from zero
	int get_max(int a, int b) {
		a += n; b += n;
		int res = INT_MIN;
		while (a <= b) {
			if (a % 2 == 1 /* right */) res = max(res, tree[a++ - 1]);
			if (b % 2 == 0 /* left  */) res = max(res, tree[b-- - 1]);
			
			a = parent(a); b = parent(b);
		}

		return res;
	}
};

int main() {
	MaxRangeTree mrt { {5, 8, 6, 3, 2, 7, 2, 6} };
	int a, b;
	cin >> a >> b;
	cout << "Maximal in range [" << a << ", " << b << "] " << mrt.get_max(a, b) << '\n';

	return 0;
}
