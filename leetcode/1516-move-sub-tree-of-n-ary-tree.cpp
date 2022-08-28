/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
    void dfs(Node *rt, int &tot, unordered_map<int, pair<Node *, pair<int, int> > > &info) {
        auto &cur = info[rt -> val];
        cur.second.first = tot++;
        for(Node *tr: rt -> children) {
            auto &nxt = info[tr -> val];
            nxt.first = rt;
            dfs(tr, tot, info);
        }
        cur.second.second = tot - 1;
    }
public:
    Node* moveSubTree(Node* root, Node* p, Node* q) {
        int tot = 0;
        unordered_map<int, pair<Node *, pair<int, int> > > info;
        dfs(root, tot, info);
        int u = p -> val, v = q -> val;
        if(info[u].first == q)
            return root;
        if(info[u].second.first <= info[v].second.first && info[v].second.second <= info[u].second.second) {
            Node *rt = info[u].first;
            if(rt != nullptr) {
                for(auto &it: rt -> children)
                    if(it == p) {
                        it = q;
                        break;
                    }
            } else {
                root = q;
            }
            rt = info[v].first;
            rt -> children.erase(remove(rt -> children.begin(), rt -> children.end(), q), rt -> children.end());
            q -> children.push_back(p);
            return root;
        }
        Node *rt = info[u].first;
        rt -> children.erase(remove(rt -> children.begin(), rt -> children.end(), p), rt -> children.end());
        q -> children.push_back(p);
        return root;
    }
};
