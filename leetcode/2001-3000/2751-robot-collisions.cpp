class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& idx, vector<int>& hp, string dir) {
        int n = idx.size();
        vector<int> ord(n), stk;
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return idx[u] < idx[v];
        });
        for(int i = 0; i < n; ++i) {
            int u = ord[i];
            // printf("parse %d\n", u);
            if(dir[u] == 'R') {
                stk.push_back(u);
            } else {
                while(!stk.empty() && dir[stk.back()] == 'R') {
                    int v = stk.back();
                    // printf("check %d (%d) %d (%d)\n", u, hp[u], v, hp[v]);
                    if(hp[v] > hp[u]) {
                        --hp[v];
                        u = -1;
                        break;
                    } else if(hp[u] > hp[v]) {
                        --hp[u];
                        stk.pop_back();
                    } else {
                        stk.pop_back();
                        u = -1;
                        break;
                    }
                }
                if(u != -1)
                    stk.push_back(u);
            }
            // for(int x: stk)
            //     printf("%d ", x);
            // puts("");
        }
        int m = stk.size();
        vector<int> res(m);
        sort(stk.begin(), stk.end());
        for(int i = 0; i < m; ++i)
            res[i] = hp[stk[i]];
        return res;
    }
};
