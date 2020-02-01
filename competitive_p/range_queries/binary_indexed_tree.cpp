#include <bits/stdc++.h>

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

void perform(std::vector<int>& tree, std::function<void(int&)> cb, int k) {
    while (k <= tree.size()) {
        cb(tree[k - 1]);
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

    int k;
    std::cin >> k;
    std::cout << sum(tree, k) << '\n';
    return 0;
}