class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> deg(n);
        for(auto &it : edges)
            ++deg[it[1]];
        vector<int> ret;
        for(int i = 0; i < n; ++i)
            if(!deg[i])
                ret.push_back(i);
        return ret;
    }
};
