#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <cmath>

long long MOD_CONST = 1e9 + 7;

std::vector<std::pair<int, int>> permutation(std::vector<int> v)
{
    std::vector<std::pair<int, int>> permutations{};
    for (int i = 0; i < v.size() - 1; ++i)
        for (int j = i + 1; j < v.size(); ++j)
            permutations.push_back({v[i], v[j]});

    return permutations;
}

class TreeEdges
{
private:
    std::vector<std::pair<int, int>> edges{};
    int node_num {};

public:
    void add(int fst, int snd)
    {
        node_num = std::max({node_num, fst, snd});
        edges.push_back(std::pair<int, int>(fst, snd));
    }

    std::vector<int> get_neighbors(int to) const
    {
        std::vector<int> neighbors {};
        for (auto edge : edges) {
            if (edge.first == to) neighbors.push_back(edge.second);
            else if (edge.second == to) neighbors.push_back(edge.first);
        }

        return neighbors;
    }

    int get_node_num() const { return node_num; }

    std::vector<std::pair<int ,int>> get_edges() const { return edges; }
};

int dist(const TreeEdges& edges, int start, int end, int i = 0, int prev = -1) {
    if (start == end) return 0;

    int distance = edges.get_node_num();
    for (auto neigh : edges.get_neighbors(start)) {
        if (neigh == prev) continue;

        if (neigh == end) {
            return i + 1;
        } else {
            distance = std::min(
                distance,
                dist(edges, neigh, end, i + 1, start)
            );
        }
    }

    return distance;
}

int calculate_expression_on(const TreeEdges& edges, std::vector<int> node_set) {
    auto perms { permutation(node_set) };
    int sum = 0;
    for (auto pr : perms)
        sum += pr.first * pr.second * dist(edges, pr.first, pr.second) % MOD_CONST;

    return sum;
}

int main(int argc, char** argv)
{
    TreeEdges edges;
    int n, q;
    std::cin >> n >> q;

    while(--n) {
        int fst, snd;
        std::cin >> fst >> snd;
        edges.add(fst, snd);
    }

    std::vector<std::vector<int>> queries;
    while(q--) {
        int node_num, node;
        std::cin >> node_num;
        std::vector<int> query_set;
        while(node_num--) {
            std::cin >> node;
            query_set.push_back(node);
        }

        queries.push_back(query_set);
    }

    for (auto query : queries) {
        std::cout << calculate_expression_on(edges, query) << '\n';
    }
}
