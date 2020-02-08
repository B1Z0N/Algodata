#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *next;
    int num;
    Node(int num) :num{num} {}
};

int main() {
    int n, m;
    Node* first, *current, *next;
    cout << "Enter n: ";
    cin >> n;
    cout << "Enter m: ";
    cin >> m;

    first = current = new Node{1};

    for (int i = 2; i <= n; ++i) {
        current = current->next = new Node{i};
    }

    current->next = first;
    current = first;

    for (int j = 1; j <= n; j++)
    {
        for(int i = 1; i < m;  i++, current = current->next);
        cout << current->num << " ";
        current->num = current->next->num;
        next = current->next;
        current->next = current->next->next;
        delete next;
    }

    cout << '\n';
}