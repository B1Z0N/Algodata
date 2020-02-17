#include <bits/stdc++.h>

using namespace std;

typedef multiset<string>::iterator It;

int main() {
    int n;
    cin >> n;
    
    multiset <string> s;
    while (n--) {
        string cmd, parm;
        cin >> cmd >> parm;
        
        if (cmd=="add") { // Add
            for (int l=0;l<parm.length();l++) 
                s.insert(parm.substr(0,l+1));
        }    
        else { // Find
            pair<It,It> ret = s.equal_range(parm);
            int count=0;
            for (auto it=ret.first;it!=ret.second;it++) count++;
            cout << count << endl;
        }
    }
    
    return 0;
}
