class TreeAncestor {
    vector<vector<int> > par;
public:
    TreeAncestor(int n, vector<int>& parent) {
        vector<vector<int> >().swap(par);
        par.push_back(parent);
        auto check = [&](vector<int> &vec) -> bool {
            for(int x : vec)
                if(x != -1)
                    return 0;
            return 1;
        };
        while(!check(par.back())) {
            vector<int> &pre = par.back(), cur;
            cur.reserve(pre.size());
            for(int i = 0; i < n; ++i) {
                cur.push_back(pre[i] == -1 ? -1 : pre[pre[i]]);
            }
            par.push_back(move(cur));
        }
    }

    int getKthAncestor(int node, int k) {
        int lim = (int)par.size();
        for(int i = 0; k > 0 && node != -1; k >>= 1, ++i)
            if(k & 1)
                node = i < lim ? par[i][node] : -1;
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */
