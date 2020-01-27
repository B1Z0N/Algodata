#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

class Node {
    vector<Node*> children {};
    int value {};
public:
    Node(int value)
        : value{value} {}
    Node() = default;                                                                      
    ~Node() {
        for (auto nd : children) delete nd;
    }

    void postorder() const {
        for (auto child : children) {
            child->postorder();
        }
        cout << value << ' ';
    }

    void setValue(int val) {
        value = val;
    }

    Node* addChild(int value) {
        Node* child = new Node{value};
        children.push_back(child);
        return child;
    }

    Node* addChild(Node* child) {
        children.push_back(child);
        return child;
    }

    unique_ptr<Node> weightsTree() const {
        return unique_ptr<Node>{_weightsTree(this)};
    }

    friend Node* _weightsTree(const Node* root) {
        if (root->children.size() == 0) return new Node{root->value};

        Node* weight_node = new Node{};
        int weight = root->value;
    
        for (auto child : root->children) {
            Node* child_sum =  _weightsTree(child);
            if (child_sum) {
                weight_node->addChild(child_sum);
                weight += child_sum->value;
            }
        }
        
        weight_node->value = weight;
        return weight_node;
    }
};

int main() {
    Node root {15};
    root.addChild(12);
    root.addChild(8);
    root.addChild(14)->addChild(13);

    root.postorder();
    cout << '\n';
    root.weightsTree()->postorder();

    return 0;
}