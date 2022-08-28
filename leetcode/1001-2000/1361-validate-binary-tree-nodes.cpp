class Solution {
public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        int cnt = 0;
        vector<int> par(n, -1);
        for(int i = 0; i < n; ++i) {
            int lch = leftChild[i], rch = rightChild[i];
            if(lch != -1) {
                if(par[lch] != -1)
                    return 0;
                par[lch] = i;
                ++cnt;
            }
            if(rch != -1) {
                if(par[rch] != -1)
                    return 0;
                par[rch] = i;
                ++cnt;
            }
        }
        if(cnt != n - 1)
            return 0;
        int rt;
        for(rt = 0; rt < n && par[rt] != -1; ++rt);
        vector<int> que;
        que.push_back(rt);
        for(int i = 0; i < (int)que.size(); ++i) {
            int u = que[i], lch = leftChild[u], rch = rightChild[u];
            if(lch != -1)
                que.push_back(lch);
            if(rch != -1)
                que.push_back(rch);
        }
        return (int)que.size() == n;
    }
};
