class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        vector<int> deg(n);
        for(auto &it: edges)
            ++deg[it[1]];
        int ret = -1;
        for(int i = 0; i < n; ++i)
            if(!deg[i]) {
                if(ret != -1)
                    return -1;
                ret = i;
            }
        return ret;
    }
};
