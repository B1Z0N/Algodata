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

int splitIntoTwo(Node wroot /* weights root */)
{
    for (auto it = begin(wroot.children); it != end(wroot.children); ++it)
    {
        int sum1 = *it->value;
        Node *current = *it;

        wroot.value -= sum1;
        auto next = wroot.children.erase(it);

        int balance = splitToBalancedForest(sum1, wroot);
        if (balance != -1) {
            return balance;
        }

        wroot.children.insert(next, current);
        wroot.value += sum1; 
    }

    for (auto child : wroot.children) {
        int balance {splitIntoTwo(*child)};
        if (balance != -1) return balance;
    }

    return -1;
}

int splitToBalancedForest(int sum1, Node root2)
{
    return 0;
}

int main()
{
    Node root = constructFrom(vector<int>{15, 12, 8, 14, 13}, vector<vector<int>>{{1, 2}, {1, 3}, {1, 4}, {4, 5}});

    root.postorder();
    cout << '\n';
    root.weightsTree().postorder();

    return 0;
}