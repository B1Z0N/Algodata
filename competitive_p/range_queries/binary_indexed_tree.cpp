#include <bits/stdc++.h>

/**
 *  Note:
 *      all of this are indexed starting from one ( [1, 2 ... n] )
 */

inline int highest_power_2(int n)
{
    return (n & (~(n - 1)));
}

std::vector<int> get_tree(const std::vector<int> &arr)
{
    std::vector<int> tree{};
    for (int k = 1; k <= arr.size(); ++k)
    {
        int p = highest_power_2(k);
        std::cout << "p: " << p << " k: " << k << '\n';
        int sum = 0;
        for (int i = k - p + 1; i <= k; ++i)
        {
            sum += arr[i - 1];
        }
        tree.push_back(sum);
    }
    return tree;
}

int sum(const std::vector<int>& tree, int k)
{
    int sum = 0;
    while (k >= 1) {
        sum += tree[k - 1];
        k -= highest_power_2(k);
    }
    return sum;
}

int sum(const std::vector<int>& tree, int a, int b)
{
    return sum(tree, b) - sum(tree, a - 1);
}

void perform(std::vector<int>& tree, std::function<void(int&)> cb, int k) {
    int prev = tree[k - 1];
    cb(tree[k - 1]);
    int next = tree[k - 1];

    while (k <= tree.size()) {
        tree[k - 1] -= prev;
        tree[k - 1] += next;
        k += highest_power_2(k);
    }
}

int main()
{
    auto tree = get_tree(std::vector<int>{1, 3, 4, 8, 6, 1, 4, 2});
    for (auto x : tree)
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    perform(tree, [](int& x) {
        x += 10;
    }, 3);

    int a, b;
    std::cin >> a >> b;
    std::cout << sum(tree, a, b) << '\n';
    return 0;
}