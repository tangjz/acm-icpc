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

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        string ret = "";
        queue<Node *> que;
        if(root != nullptr)
            que.push(root);
        que.push(nullptr);
        while(!que.empty()) {
            Node *u = que.front();
            que.pop();
            if(u == nullptr) {
                ret += "null,";
            } else {
                ret += to_string(u -> val) + ",";
                for(Node *v: u -> children)
                    que.push(v);
                que.push(nullptr);
            }
        }
        int pos = ret.size();
        for( ; pos >= 5 && ret.substr(pos - 5, 5) == "null,"; pos -= 5);
        ret.resize(pos);
        ret.pop_back();
        return ret;
    }

    // Decodes your encoded data to tree.
    Node* deserialize(string_view data) {
        Node *ret = nullptr;
        queue<Node *> que;
        int n = data.size();
        for(int i = 0, j = 0; i < n; i = j + 1) {
            j = i;
            if(!i) {
                for( ; j < n && data[j] != ','; ++j);
                string_view item = data.substr(i, j - i);
                if(item != "null") {
                    ret = new Node(stoi(string(item)));
                    que.push(ret);
                    for(++j; j < n && data[j] != ','; ++j);
                }
                continue;
            }
            Node *u = que.front();
            for( ; j < n && data[j] != ','; ++j);
            string_view item = data.substr(i, j - i);
            if(item == "null") {
                que.pop();
            } else {
                u -> children.push_back(new Node(stoi(string(item))));
                que.push(u -> children.back());
            }
        }
        return ret;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
