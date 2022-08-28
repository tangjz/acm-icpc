class Solution {
    void dfs(int u, vector<vector<int> > &edges, vector<int> &nums, vector<set<int> > &Hash, vector<int> &ret) {
        Hash[u].insert(nums[u]);
        for(int v: edges[u]) {
            dfs(v, edges, nums, Hash, ret);
            ret[u] = max(ret[u], ret[v]);
            if(Hash[u].size() < Hash[v].size()) {
                swap(Hash[u], Hash[v]);
            }
            for(int x: Hash[v])
                Hash[u].insert(x);
            set<int>().swap(Hash[v]);
        }
        while(Hash[u].count(ret[u]))
            ++ret[u];
    }    
public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = parents.size();
        vector<vector<int> > edges(n);
        for(int i = 1; i < n; ++i)
            edges[parents[i]].push_back(i);
        vector<int> ret(n, 1);
        vector<set<int> > Hash(n);
        dfs(0, edges, nums, Hash, ret);
        return ret;
    }
};
