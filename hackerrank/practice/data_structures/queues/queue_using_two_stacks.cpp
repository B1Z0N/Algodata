#include <bits/stdc++.h>

using namespace std;

class quaue {
	stack<int> st;
public:

	quaue() = default;
	
	void push(int val) {
		st.push(val);
	}

	void pop() {
		if (st.size() == 1) st.pop();
		else {
			int temp = st.top();
			st.pop();
			pop();
			st.push(temp);
		}
	}
	
	int front() {
		if (st.size() == 1) return st.top();
		else {
			int temp = st.top();
			st.pop();
			int res = front();
			st.push(temp);
			return res;
		}
	}
};

int main() {
	int n;
	cin >> n;
	quaue q;
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
