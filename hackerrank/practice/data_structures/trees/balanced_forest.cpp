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
        : value{value}, children{children}, parent{parent}, subthis{subthis}
    {
        for (auto child : children)
        {
            child->parent = parent;
        }
    }
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

struct Edge
{
    Edge(int v1, int v2) : v1{v1}, v2{v2} {}
    int v1;
    int v2;
    bool visited{false};
};

class Forest : public GeneralForest<Forest>
{
public:
    Forest(int value, Forest *parent = nullptr, list<Forest *> children = list<Forest *>{})
        : GeneralForest{this, value, parent, children} {}
    Forest() : GeneralForest{this} {}
    friend class WeightForest;

    static Forest from(vector<int> &&c, vector<Edge> &&edges)
    {
        Forest root{c[0]};
        // adding dummy 0-value node to root,
        // so that we had at least 3 nodes in the tree
        c.push_back(0);
        edges.push_back(Edge{1, c.size()});
        _from(c, edges, &root);
        return root;
    }

private:
    friend void _from(const vector<int> &c, vector<Edge> &edges, Forest *root, int i = 1)
    {
        for (auto &edge : edges)
        {
            if (edge.visited)
                continue;

            if (edge.v1 == i || edge.v2 == i)
            {
                if (edge.v2 == i)
                    swap(edge.v1, edge.v2);
                root->addChild(c[edge.v2 - 1]);
                edge.visited = true;
                _from(c, edges, root->children.back(), edge.v2);
            }
        }
    }
};

class WeightForest : public GeneralForest<WeightForest>
{
    bool visited {false};
public:
    WeightForest(int value, WeightForest *parent = nullptr, list<WeightForest *> children = list<WeightForest *>{})
        : GeneralForest{this, value, parent, children} {}
    WeightForest() : GeneralForest{this} {}

    static WeightForest from(const Forest *root)
    {
        WeightForest wroot{root->value, nullptr};
        _from(root, &wroot);
        return wroot;
    }

    int balancing()
    {
        int balance = firstCut(this);
        return balance == INT_MAX ? -1 : balance;
    }

private:
    static WeightForest *_from(const Forest *root, WeightForest *wroot = nullptr)
    {
        // just a workaround to pass in stack-acllocated weighted root
        WeightForest *weight_node = wroot == nullptr ? new WeightForest{root->value} : wroot;
        for (auto child : root->children)
        {
            WeightForest *child_sum = _from(child);
            weight_node->addChild(child_sum);
            weight_node->value += child_sum->value;
        }

        return weight_node;
    }

    int firstCut(WeightForest *par, int global_balance = INT_MAX)
    {
        int balance;
        auto it = par->children.begin();
        auto end = par->children.end();
        while (it != end)
        {
            WeightForest *current = *it;
            auto next_it = cutChild(it);
            finalPseudoCut(this, current->value, global_balance);
            it = insertChild(next_it, current, par);
        }

        for (auto child : par->children)
        {
            balance = firstCut(child, global_balance);
            if (balance != -1 && balance < global_balance)
                global_balance = balance;
            child->visited = true;
        }

        return global_balance;
    }

    int finalPseudoCut(WeightForest *par, int sum1, int &global_balance)
    {
        int balance;
        for (auto child : par->children)
        {
            if (child->visited) continue;
            int sum2 = child->value;
            int sum3 = this->value - child->value;
            balance = balanceAmong(sum1, sum2, sum3);
            if (balance != -1 && balance < global_balance)
                global_balance = balance;
        }

        for (auto child : par->children)
        {
            if (child->visited) continue;
            balance = finalPseudoCut(child, sum1, global_balance);
            if (balance != -1 && balance < global_balance)
                global_balance = balance;
        }

        return global_balance;
    }

    int balanceAmong(int sum1, int sum2, int sum3)
    {
        if (sum1 == sum2 && sum1 >= sum3)
        {
            return sum1 - sum3;
        }
        else if (sum2 == sum3 && sum2 >= sum1)
        {
            return sum2 - sum1;
        }
        else if (sum1 == sum3 && sum1 >= sum2)
        {
            return sum1 - sum2;
        }

        return -1;
    }

    friend list<WeightForest *>::iterator cutChild(list<WeightForest *>::iterator it)
    {
        WeightForest *current = *it;
        int cut_weight = current->value;
        while (current->parent != nullptr)
        {
            current = current->parent;
            current->value -= cut_weight;
        }

        current = *it;
        it = current->parent->children.erase(it);
        current->parent = nullptr;

        return it;
    }

    friend list<WeightForest *>::iterator insertChild(list<WeightForest *>::iterator next_it, WeightForest *current, WeightForest *par)
    {
        current->parent = par;
        auto inserted = par->children.insert(next_it, current);

        int insert_weight = current->value;
        while (par != nullptr)
        {
            par->value += insert_weight;
            par = par->parent;
        }

        return ++inserted;
    }
};

// Complete the balancedForest function below.
int balancedForest(vector<int> &&c, vector<Edge> &&edges)
{
    Forest root = Forest::from(std::move(c), std::move(edges));
    root.postorder();
    cout << '\n';
    WeightForest wroot = WeightForest::from(&root);
    wroot.postorder();
    cout << '\n';
    return wroot.balancing();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string c_temp_temp;
        getline(cin, c_temp_temp);

        vector<string> c_temp = split_string(c_temp_temp);

        vector<int> c(n);

        for (int i = 0; i < n; i++)
        {
            int c_item = stoi(c_temp[i]);

            c[i] = c_item;
        }

        vector<Edge> edges;
        int first, second;
        while (--n)
        {
            cin >> first >> second;
            edges.push_back(Edge{first, second});

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int result = balancedForest(std::move(c), std::move(edges));

        fout << result << "\n";
        cout << result << "\n";
    }

    fout.close();

    return 0;
}

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
