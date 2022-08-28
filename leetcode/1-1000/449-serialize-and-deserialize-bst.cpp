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
    TreeNode *dfs(int L, int R, vector<int> &vals, vector<int> &pR) {
        if(L > R)
            return nullptr;
        TreeNode *rt = new TreeNode(vals[L]);
        int M = pR[L];
        rt -> left = dfs(L + 1, M - 1, vals, pR);
        rt -> right = dfs(M, R, vals, pR);
        return rt;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == nullptr)
            return "";
        string ret = to_string(root -> val);
        for(TreeNode *tr: {root -> left, root -> right}) {
            string tmp = serialize(tr);
            if(!tmp.empty())
                ret += "," + tmp;
        }
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.empty())
            return nullptr;
        vector<int> vals;
        for(int i = 0, n = data.size(); i < n; ++i) {
            int j = i;
            for( ; i < n && data[i] >= '0' && data[i] <= '9'; ++i);
            vals.push_back(stoi(data.substr(j, i - j)));
        }
        int m = vals.size();
        vector<int> pR(m);
        for(int i = m - 1; i >= 0; --i)
            for(pR[i] = i + 1; pR[i] < m && vals[i] > vals[pR[i]]; pR[i] = pR[pR[i]]);
        return dfs(0, m - 1, vals, pR);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
