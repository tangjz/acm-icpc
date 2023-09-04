class Solution {
public:
    bool isPreorder(vector<vector<int>>& nodes) {
        int n = nodes.size(), m = 0;
        vector<pair<int, int> > stk(n);
        if(nodes[0][1] != -1)
            return 0;
        stk[m++] = {nodes[0][0], 0};
        for(int i = 1; i < n; ++i) {
            int u = nodes[i][0], p = nodes[i][1];
            for( ; m > 0 && stk[m - 1].first != p; --m);
            if(!m || stk[m - 1].second == 2)
                return 0;
            ++stk[m - 1].second;
            stk[m++] = {u, 0};
        }
        return 1;
    }
};