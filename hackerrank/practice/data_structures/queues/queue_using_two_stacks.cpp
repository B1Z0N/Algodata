#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	queue<int> q;
	while (n--) {
		int type, value;
		cin >> type;
		if (type == 1) {
			cin >> value;
			q.push(value);
		} else if (type == 2) {
			q.pop(); 	
		} else if (type == 3) {
			cout << q.front() << '\n';
		}
	}
	
	return 0;
}
