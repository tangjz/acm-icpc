class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        if(trust.empty()) {
            return n > 1 ? -1 : 1;
        }
        vector<int> deg(n + 1);
        for(auto &it: trust) {
            deg[it[0]] = -n;
            ++deg[it[1]];
        }
        int v = n;
        for( ; v && deg[v] != n - 1; --v);
        return v > 0 ? v : -1;
    }
};
