#include <bits/stdc++.h>

inline int left(int parent) {
    return 2 * parent;
}

inline int right(int parent) {
    return 2 * parent + 1;
}

inline int parent(int child) {
    return child / 2;
}

std::vector<int> tree(std::vector<int> vec) {
    int size = vec.size();
    std::vector<int> res (size - 1);
    std::copy(vec.begin(), vec.end(), std::back_inserter(res));
    for (int i = size - 1; i >= 1; --i) {
        res[i - 1] = res[left(i) - 1] + res[right(i) - 1];
    }
    return res;
}

int sum(const std::vector<int>& tree, int a, int b) {
    int n = tree.size() / 2, sum = 0;
    a += n; b += n;
    while (a  <= b) {
        if (a % 2 == 1 /* it's right */)  sum += tree[a++ - 1];
        if (b % 2 == 0 /* it's left */) sum += tree[b-- - 1];
        a = parent(a); b = parent(b);
    }
    return sum;
}

void perform(std::vector<int>& tree, int k, std::function<void(int&)> cb) {
    int n = tree.size() / 2;
    k += n;
    int prev = tree[k - 1];
    cb(tree[k - 1]);
    int next = tree[k - 1];
    k = parent(k);
    while(k >= 1) {
        tree[k - 1] -= prev;
        tree[k - 1] += next;
        k = parent(k);
    }
}

int main() {
    auto tr = tree(std::vector<int>{5, 8, 6, 3, 2 ,7, 2 ,6});
    for (auto& x : tr) {
        std::cout << x << ' ';
    }
    std::cout << '\n';


    perform(tr, 3, [](int& b) {
        b += 2;
    });
    for (auto& x : tr) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    int a, b;
    std::cin >> a >> b;
    std::cout << sum(tr, a, b);
    return 0;
}