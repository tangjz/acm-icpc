class Solution {
    vector<int> calc(int n, vector<vector<int> > &edges) {
        vector<int> deg(n), ord, rnk(n);
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[--it[0]].push_back(--it[1]);
            ++deg[it[1]];
        }
        for(int i = 0; i < n; ++i)
            if(!deg[i])
                ord.push_back(i);
        for(int i = 0; i < n; ++i) {
            if(i >= (int)ord.size())
                return {};
            int u = ord[i];
            rnk[u] = i;
            for(int v: e[u])
                if(!(--deg[v]))
                    ord.push_back(v);
        }
        return rnk;
    }
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<int> rowRank = calc(k, rowConditions);
        if(rowRank.empty())
            return {};
        vector<int> colRank = calc(k, colConditions);
        if(colRank.empty())
            return {};
        vector<vector<int> > mat(k, vector<int>(k));
        for(int i = 0; i < k; ++i)
            mat[rowRank[i]][colRank[i]] = i + 1;
        return mat;
    }
};
