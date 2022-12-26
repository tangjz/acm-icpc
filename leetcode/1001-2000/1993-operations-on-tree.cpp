class LockingTree {
    int n;
    vector<int> par, in, out, seq, ack;
    vector<vector<int> > e;
    void dfs(int u) {
        seq.push_back(u);
        in[u] = seq.size() - 1;
        for(int v: e[u]) {
            dfs(v);
        }
        out[u] = seq.size() - 1;
    }

public:
    LockingTree(vector<int>& parent) {
        par = move(parent);
        n = par.size();
        vector<int>(n).swap(in);
        vector<int>(n).swap(out);
        vector<int>(n).swap(ack);
        vector<vector<int> >(n).swap(e);
        vector<int>().swap(seq);
        for(int i = 1; i < n; ++i)
            e[par[i]].push_back(i);
        dfs(0);
    }

    bool lock(int num, int user) {
        if(ack[num])
            return false;
        ack[num] = user;
        return true;
    }

    bool unlock(int num, int user) {
        if(ack[num] != user)
            return false;
        ack[num] = 0;
        return true;
    }

    bool upgrade(int num, int user) {
        for(int u = num; u != -1; u = par[u])
            if(ack[u])
                return false;
        bool found = false;
        for(int i = in[num] + 1; i <= out[num]; ++i) {
            if(ack[seq[i]]) {
                found = true;
                break;
            }
        }
        if(!found)
            return false;
        ack[num] = user;
        for(int i = in[num] + 1; i <= out[num]; ++i)
            ack[seq[i]] = 0;
        return true;
    }
};

/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->lock(num,user);
 * bool param_2 = obj->unlock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */
