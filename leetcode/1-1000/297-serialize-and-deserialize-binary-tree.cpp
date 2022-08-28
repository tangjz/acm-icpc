/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == NULL)
            return "[]";
        string buf = "[" + to_string(root -> val);
        queue<TreeNode *> que;
        que.push(root);
        auto append = [&](TreeNode *cur) {
            buf += ',';
            if(cur == NULL) {
                buf += "null";
            } else {
                buf += to_string(cur -> val);
                que.push(cur);
            }
        };
        while(!que.empty()) {
            TreeNode *cur = que.front();
            que.pop();
            append(cur -> left);
            append(cur -> right);
        }
        while((int)buf.length() >= 5 && buf.substr(buf.length() - 5, 5) == ",null")
            buf.erase(buf.length() - 5, 5);
        buf += ']';
        return buf;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "[]")
            return NULL;
        int pos = 1, nxt;
        for(nxt = pos; data[nxt] != ',' && data[nxt] != ']'; ++nxt);
        TreeNode *root = new TreeNode(stoi(data.substr(pos, nxt - pos)));
        pos = nxt + 1;
        queue<TreeNode *> que;
        que.push(root);
        while(!que.empty()) {
            TreeNode *cur = que.front();
            que.pop();
            if(pos < (int)data.length()) {
                for(nxt = pos; data[nxt] != ',' && data[nxt] != ']'; ++nxt);
                string buf = data.substr(pos, nxt - pos);
                pos = nxt + 1;
                if(buf == "null") {
                    cur -> left = NULL;
                } else {
                    cur -> left = new TreeNode(stoi(buf));
                    que.push(cur -> left);
                }
            }
            if(pos < (int)data.length()) {
                for(nxt = pos; data[nxt] != ',' && data[nxt] != ']'; ++nxt);
                string buf = data.substr(pos, nxt - pos);
                pos = nxt + 1;
                if(buf == "null") {
                    cur -> right = NULL;
                } else {
                    cur -> right = new TreeNode(stoi(buf));
                    que.push(cur -> right);
                }
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
