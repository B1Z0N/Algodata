#define pb push_back
typedef std::vector<bool> vb;
typedef long long ll;

class Solution {
public:
    int kthGrammar(int N, int K) {
        if (N == 1) return 0;
        
        int prevK = (K + 1) / 2;
        bool is_even = ((K + 1) % 2 != 0);
        return kthGrammar(N - 1, prevK) ? !is_even : is_even;
    }
};
