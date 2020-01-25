#include <bits/stdc++.h>

using namespace std;

struct Node
{
    using val_ptr = pair<int, Node **>;

    Node(int val)
        : value{val}
    {
    }

    Node(const vector<vector<int>> &indexes)
    {
        value = 1;
        int i = 0;
        queue<val_ptr> q{};
        
        pair<int, int> current {indexes[i][0], indexes[i][1]};
        if (current.first != -1)
            q.push(val_ptr{current.first, &left});
        if (current.second != -1)
            q.push(val_ptr{current.second, &right});
        ++i;

        while (!q.empty())
        {
            int val = q.front().first;
            Node ** cur = q.front().second;
            *cur = new Node {val}; 

            current = pair<int, int> {indexes[i][0], indexes[i][1]};
            if (current.first != -1) 
                q.push(val_ptr{current.first, &((*cur)->left)});
            if (current.second  != -1)
                q.push(val_ptr{current.second, &((*cur)->right)});
            ++i;

            q.pop();
        }
    }

    void swap_nodes(int k, int depth = 1)
    {
        if (depth % k == 0)
            std::swap(left, right);

        if (left)
            left->swap_nodes(k, depth + 1);
        if (right)
            right->swap_nodes(k, depth + 1);
    }

    void inorder(vector<int> &res)
    {
        if (left)
            left->inorder(res);
        res.push_back(value);
        if (right)
            right->inorder(res);
    }

    ~Node()
    {
        delete left;
        delete right;
    }

    Node *left{};
    Node *right{};
    int value;
};

/*
 * Complete the swapNodes function below.
 */
vector<vector<int>>
swapNodes(vector<vector<int>> indexes, vector<int> queries)
{
    /*
     * Write your code here.
     */
    Node root{indexes};
    vector<vector<int>> results{};
    for (auto k : queries)
    {
        root.swap_nodes(k);
        vector<int> res{};
        root.inorder(res);
        results.push_back(res);
    }

    return results;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> indexes(n);
    for (int indexes_row_itr = 0; indexes_row_itr < n; indexes_row_itr++)
    {
        indexes[indexes_row_itr].resize(2);

        for (int indexes_column_itr = 0; indexes_column_itr < 2; indexes_column_itr++)
        {
            cin >> indexes[indexes_row_itr][indexes_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(queries_count);

    for (int queries_itr = 0; queries_itr < queries_count; queries_itr++)
    {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[queries_itr] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (int result_row_itr = 0; result_row_itr < result.size(); result_row_itr++)
    {
        for (int result_column_itr = 0; result_column_itr < result[result_row_itr].size(); result_column_itr++)
        {
            fout << result[result_row_itr][result_column_itr];

            if (result_column_itr != result[result_row_itr].size() - 1)
            {
                fout << " ";
            }
        }

        if (result_row_itr != result.size() - 1)
        {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
