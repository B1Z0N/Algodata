#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct Node
{
    list<Node *> children{};
    int value{};

    Node(int value)
        : value{value} {}
    Node() = default;
    ~Node()
    {
        for (auto nd : children)
            delete nd;
    }

    void postorder() const
    {
        for (auto child : children)
        {
            child->postorder();
        }
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

    Node *addChild(int value)
    {
        Node *child = new Node{value};
        children.push_back(child);
        return child;
    }

    Node *addChild(Node *child)
    {
        children.push_back(child);
        return child;
    }

    Node weightsTree() const
    {
        return *_weightsTree(this);
    }

    friend Node *_weightsTree(const Node *root)
    {
        if (root->children.size() == 0)
            return new Node{root->value};

        Node *weight_node = new Node{};
        int weight = root->value;

        for (auto child : root->children)
        {
            Node *child_sum = _weightsTree(child);
            if (child_sum)
            {
                weight_node->addChild(child_sum);
                weight += child_sum->value;
            }
        }

        weight_node->value = weight;
        return weight_node;
    }
};

void _constructFrom(const vector<int> &c, const vector<vector<int>> &edges, Node *root, int i = 1)
{
    root->setValue(c[i - 1]);
    for (auto edge : edges)
    {
        if (edge[0] == i)
            _constructFrom(c, edges, root->addChild(edge[1]), edge[1]);
    }
}

Node constructFrom(vector<int> &&c, vector<vector<int>> &&edges)
{
    Node root{};
    // adding dummy 0-value node to root,
    // so that we had at least 3 nodes in the tree
    c.push_back(0);
    edges.push_back(vector<int>{1, c.size()});
    _constructFrom(c, edges, &root);
    return root;
}

int splitToBalancedForest(int sum1, Node *root2, Node *root = nullptr)
{
    if (root == nullptr)
        root = root2;

    for (auto child : root2->children)
    {
        int sum2 = child->value;
        int sum3 = root->value - child->value;

        if (sum2 == sum1)
        {
            return abs(sum3 - sum1);
        }
        else if (sum3 == sum1)
        {
            return abs(sum2 - sum1);
        }

        int balance = splitToBalancedForest(sum1, child, root);
        if (balance != -1)
            return balance;
    }

    return -1;
}

int splitIntoTwo(Node *wroot /* weights root */)
{
    for (auto it = begin(wroot->children); it != end(wroot->children); ++it)
    {
        // cut some edge leading to children node
        Node *current = *it;
        auto next = wroot->children.erase(it);
        wroot->value -= current->value;

        // try to find the balance with part that is left after cutting
        int balance = splitToBalancedForest(current->value, wroot);

        // restore, if there are no way of such splitting
        wroot->children.insert(next, current);
        wroot->value += current->value;

        // finally return minimal balance found
        if (balance != -1)
            return balance;
    }

    // call this func on each child node
    for (auto child : wroot->children)
    {
        int balance{splitIntoTwo(child)};
        if (balance != -1)
            return balance;
    }

    return -1;
}

// Complete the balancedForest function below.
int balancedForest(vector<int>&& c, vector<vector<int>>&& edges)
{
    cout << 1 << '\n';
    Node wroot = constructFrom(std::move(c), std::move(edges)).weightsTree();
    return splitIntoTwo(&wroot);
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

        vector<vector<int>> edges(n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            edges[i].resize(2);

            for (int j = 0; j < 2; j++)
            {
                cin >> edges[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int result = balancedForest(std::move(c), std::move(edges));

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