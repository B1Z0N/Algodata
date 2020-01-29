#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

class Forest;
class WeightForest;

template <typename ChildT>
class GeneralForest
{
    // 'this' pointer of subclass
    ChildT *subthis;

protected:
    list<ChildT *> children{};
    ChildT *parent{};
    int value{};

public:
    GeneralForest(ChildT *subthis, int value, ChildT *parent = nullptr, list<ChildT *> children = list<ChildT *>{})
        : value{value}, children{children}, parent{parent}, subthis{subthis} {}
    GeneralForest(ChildT *subthis) : subthis{subthis} {}
    GeneralForest() = delete;
    ~GeneralForest()
    {
        for (auto child : children)
            delete child;
    }

    void preorder() const
    {
        cout << value << ' ';
        for (auto child : children)
            child->postorder();
    }

    void postorder() const
    {
        for (auto child : children)
            child->postorder();
        cout << value << ' ';
    }

    void setValue(int val)
    {
        value = val;
    }

    int getValue()
    {
        return value;
    }

    void addChild(int value)
    {
        children.push_back(new ChildT{value});
        children.back()->parent = subthis;
    }

    void addChild(ChildT *child)
    {
        children.push_back(child);
        child->parent = subthis;
    }
};

class Forest : public GeneralForest<Forest>
{
public:
    Forest(int value, Forest *parent = nullptr, list<Forest *> children = list<Forest *>{})
        : GeneralForest{this, value, parent, children} {}
    Forest() : GeneralForest{this} {}
    friend class WeightForest;

    static Forest from(vector<int> c, vector<vector<int>> edges)
    {
        Forest root{};
        // adding dummy 0-value node to root,
        // so that we had at least 3 nodes in the tree
        c.push_back(0);
        edges.push_back(vector<int>{1, c.size()});
        _from(c, edges, &root);
        return root;
    }

private:
    friend void _from(const vector<int> &c, const vector<vector<int>> &edges, Forest *root, Forest *parent = nullptr, int i = 1)
    {
        root->value = c[i - 1];
        root->parent = parent;
        for (auto edge : edges)
            if (edge[0] == i)
            {
                // push back new child
                root->addChild(edge[1]);
                _from(c, edges, root->children.back(), root, edge[1]);
            }
    }
};

class WeightForest : public GeneralForest<WeightForest>
{
public:
    WeightForest(int value, WeightForest *parent = nullptr, list<WeightForest *> children = list<WeightForest *>{})
        : GeneralForest{this, value, parent, children} {}
    WeightForest() : GeneralForest{this} {}

    static WeightForest from(const Forest *root)
    {
        WeightForest wroot{root->value, nullptr};
        _from(root, nullptr, &wroot);
        return wroot;
    }

    int balancing()
    {
        return firstCut(this);
    }

    // friend pair<unique_ptr<Forest>, list<Forest *>::iterator> cutWeightNode(Forest *parent, list<Forest *>::iterator child_it)
    // {
    //     Forest *current = *child_it;
    //     int cut_weight = current->value;
    //     while (current->parent != nullptr)
    //     {
    //         current = current->parent;
    //         current->value -= cut_weight;
    //     }
    //     current = *child_it;
    //     auto next = parent->children.erase(child_it);

    //     return {unique_ptr<Forest>{current}, next};
    // }

    // friend void insertWeightNode(list<Forest *>::iterator child_it, list<Forest *>::iterator after_child_it)
    // {
    //     Forest *current = *child_it;
    //     Forest *parent = *affter_child_it->parent;
    //     parent->children.insert(after_child_it, child_it);
    //     int insert_weight = current->value;
    //     while (parent != nullptr)
    //     {
    //         parent->value += insert_weight;
    //         parent = parent->parent;
    //     }
    // }

private:
    static WeightForest *_from(const Forest *root, WeightForest *parent = nullptr, WeightForest *wroot = nullptr)
    {
        // just a workaround to pass in stack-acllocated weighted root
        WeightForest *weight_node = wroot == nullptr ? new WeightForest{root->value, parent} : wroot;
        for (auto child : root->children)
        {
            WeightForest *child_sum = _from(child, weight_node);
            weight_node->addChild(child_sum);
            weight_node->value += child_sum->value;
        }

        return weight_node;
    }

    int firstCut(const WeightForest *parent, int global_balance = INT_MAX)
    {
        int balance;
        auto it = parent->children.begin();
        auto end = parent->children.end();
        while (it != end)
        {
            WeightForest *current = *it;
            auto next_it = cutChild(it);

            finalPseudoCut(this, current->value, global_balance);

            it = insertChild(it, next_it);
        }

        for (auto child : parent->children)
        {
            balance = firstCut(child, global_balance);
            if (balance != -1 && balance < global_balance)
                global_balance = balance;
        }

        return global_balance;
    }

    int finalPseudoCut(const WeightForest* parent, int sum1, int& global_balance)
    {
        int balance;
        for (auto child : parent->children)
        {
            int sum2 = child->value;
            int sum3 = this->value - child->value;
            balance = balanceAmong(sum1, sum2, sum3);
            if (balance != -1 && balance < global_balance)
                global_balance = balance;
        }

        for (auto child : parent->children)
        {
            balance = finalPseudoCut(child, sum1, global_balance);
            if (balance != -1 && balance < global_balance)
                global_balance = balance;
        }

        return global_balance;
    }

    int balanceAmong(int sum1, int sum2, int sum3) {
            if (sum1 == sum2 && sum1 > sum3) {
                return sum1 - sum3;
            } else if (sum2 == sum3 && sum2 > sum1) {
                return sum2 - sum1;
            } else if (sum1 == sum3 && sum1 > sum2){
                return sum1 - sum2;
            }

            return -1;
    }
};

int main()
{
    Forest root = Forest::from(vector<int>{15, 12, 8, 14, 13}, vector<vector<int>>{{1, 2}, {1, 3}, {1, 4}, {4, 5}});
    WeightForest wroot = WeightForest::from(&root);
    root.postorder();
    cout << '\n';
    wroot.postorder();
    cout << '\n';

    return 0;
}

// // Complete the balancedForest function below.
// int balancedForest(vector<int> &&c, vector<vector<int>> &&edges)
// {
//     Forest wroot = Forest::from(std::move(c), std::move(edges));
//     return wroot.balancing();
// }

// int main()
// {
//     ofstream fout(getenv("OUTPUT_PATH"));

//     int q;
//     cin >> q;
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');

//     for (int q_itr = 0; q_itr < q; q_itr++)
//     {
//         int n;
//         cin >> n;
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');

//         string c_temp_temp;
//         getline(cin, c_temp_temp);

//         vector<string> c_temp = split_string(c_temp_temp);

//         vector<int> c(n);

//         for (int i = 0; i < n; i++)
//         {
//             int c_item = stoi(c_temp[i]);

//             c[i] = c_item;
//         }

//         vector<vector<int>> edges(n - 1);
//         for (int i = 0; i < n - 1; i++)
//         {
//             edges[i].resize(2);

//             for (int j = 0; j < 2; j++)
//             {
//                 cin >> edges[i][j];
//             }

//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         }

//         int result = balancedForest(std::move(c), std::move(edges));

//         cout << result << "\n";
//         fout << result << "\n";
//     }

//     fout.close();

//     return 0;
// }

vector<string> split_string(string input_string)
{
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ')
    {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos)
    {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
