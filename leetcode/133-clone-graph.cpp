/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(node == nullptr)
            return nullptr;
        unordered_map<int, Node *> hs;
        vector<Node *> que;
        hs[node -> val] = new Node(node -> val);
        que.push_back(node);
        for(int i = 0; i < (int)que.size(); ++i) {
            Node *cur = que[i];
            vector<Node *> adj;
            for(Node *nxt: cur -> neighbors) {
                auto it = hs.find(nxt -> val);
                if(it != hs.end()) {
                    adj.push_back(it -> second);
                    continue;
                }
                adj.push_back(hs[nxt -> val] = new Node(nxt -> val));
                que.push_back(nxt);
            }
            hs[cur -> val] -> neighbors = move(adj);
        }
        return hs[node -> val];
    }
};
