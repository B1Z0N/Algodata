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

public:
	MaxRangeTree(const vector<int>& arr) :tree{max_tree(arr)} {}

	int get_max(int a, int b) {
		return 0;
	}
};

int main() {
	MaxRangeTree mrt { {5, 8, 6, 3, 2, 7, 2, 6} };

	return 0;
}
