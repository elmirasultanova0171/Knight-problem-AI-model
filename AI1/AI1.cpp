#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

struct Node {
    pair<int, int> state;
    Node* parent;

    Node(pair<int, int> state, Node* parent = nullptr) {
        this->state = state;
        this->parent = parent;
    }
};

struct PairHash {
    template<typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

class KnightProblem {
private:
    int n;

public:
    KnightProblem(int n) {
        this->n = n;
    }

    unordered_set<pair<int, int>, PairHash> actions(pair<int, int> state) {
        int r = state.first;
        int c = state.second;
        unordered_set<pair<int, int>, PairHash> moves = {
            {r + 1, c + 2}, {r + 2, c + 1}, {r + 2, c - 1}, {r + 1, c - 2},
            {r - 1, c - 2}, {r - 2, c - 1}, {r - 2, c + 1}, {r - 1, c + 2}
        };

        unordered_set<pair<int, int>, PairHash> valid_moves;
        for (auto move : moves) {
            if (move.first >= 0 && move.first < n && move.second >= 0 && move.second < n) {
                valid_moves.insert(move);
            }
        }
        return valid_moves;
    }

    pair<int, int> result(pair<int, int> state, pair<int, int> action) {
        return action;
    }

    bool goal_test(pair<int, int> state) {
        return (state.second == n - 1) && (state.first == n - 1);
    }

    int h(Node* node) {
        return 0;
    }

    pair<int, int> initial() {
        return { 0, 0 };
    }
};

void print_path(Node* node) {
    vector<pair<int, int>> path;
    while (node != nullptr) {
        path.push_back(node->state);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    for (auto p : path) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << endl;
}

Node* breadth_first_search(KnightProblem problem) {
    auto initial_node = new Node(problem.initial());
    if (problem.goal_test(initial_node->state)) {
        return initial_node;
    }
    queue<Node*> frontier;
    frontier.push(initial_node);
    unordered_set<pair<int, int>, PairHash> explored;
    while (!frontier.empty()) {
        auto node = frontier.front();
        frontier.pop();
        explored.insert(node->state);
        for (auto action : problem.actions(node->state)) {
            auto child_state = problem.result(node->state, action);
            if (explored.find(child_state) == explored.end()) {
                auto child_node = new Node(child_state, node);
                if (problem.goal_test(child_state)) {
                    return child_node;
                }
                frontier.push(child_node);
            }
        }
    }
    return nullptr;
}
int main() {
    int n = 5;
    KnightProblem problem(n);
    auto solution_node = breadth_first_search(problem);
    if (solution_node == nullptr) {
        cout << "No solution found for n=" << n << endl;
    } else {
        cout << "Solution path: ";
        print_path(solution_node);
    }
    return 0;
}
