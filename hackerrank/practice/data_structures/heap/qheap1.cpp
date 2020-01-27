#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Heap
{
    vector<int> vec {};

public:
    void add(int elem)
    {
        vec.push_back(elem);
        for (int i = vec.size() - 1; i > 0 && vec[parent(i)] > vec[i]; i = parent(i))
            swap(vec[i], vec[parent(i)]);
    }

    void del(int elem)
    {
        for (int i = 0; i < vec.size(); ++i)
        {
            if (vec[i] == elem)
            {
                delIndex(i);
                return;
            }
        }
    }

    int min()
    {
        return vec.front();
    }

private:
    void delIndex(int i)
    {
        vec[i] = vec.back();
        vec.pop_back();
        heapify(i);
    }

    void heapify(int i)
    {
        int smallest = i;  // Initialize smalles as root
        int l = left(i);
        int r = right(i);
        int n = vec.size();

        // If left child is smaller than root
        if (l < n && vec[l] < vec[smallest])
            smallest = l;

        // If right child is smaller than smallest so far
        if (r < n && vec[r] < vec[smallest])
            smallest = r;

        // If smallest is not root
        if (smallest != i)
        {
            swap(vec[i], vec[smallest]);
            // Recursively heapify the affected sub-tree
            heapify(smallest);
        }
    }

    inline int parent(int i)
    {
        return (i - 1) / 2;
    }
    inline int left(int i)
    {
        return 2 * i + 1;
    }
    inline int right(int i)
    {
        return 2 * i + 2;
    }
};

int main()
{
    int n;
    cin >> n;
    Heap heap{};
    while (n--)
    {
        int op, on;
        cin >> op;
        if (op == 1)
        {
            cin >> on;
            heap.add(on);
        }
        else if (op == 2)
        {
            cin >> on;
            heap.del(on);
        }
        else if (op == 3)
        {
            cout << heap.min() << '\n';
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
