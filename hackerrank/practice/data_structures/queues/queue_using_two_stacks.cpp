#include <bits/stdc++.h>

using namespace std;

class quaue {
	stack<int> rear;
	stack<int> front;
public:

	quaue() = default;
	
	void push(int val) {
		rear.push(val);
	}

   	void  pop() { 
        	if (rear.empty() && front.empty()) return; // just to ensure that tests timed out
        	
		if (front.empty()) { 
            		while (!rear.empty()) { 
                		front.push(rear.top()); 
                		rear.pop(); 
            		} 
        	} 
  
        	front.pop(); 
	}

	int frontt() {
	    	if (rear.empty() && front.empty()) return -1; // just to ensure that tests timed out
        	
		if (front.empty()) { 
            		while (!rear.empty()) { 
                		front.push(rear.top()); 
                		rear.pop(); 
            		} 
        	} 
  
        	return  front.top(); 
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
			cout << q.frontt() << '\n';
		}
	}
	
	return 0;
}
