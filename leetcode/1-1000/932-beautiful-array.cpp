class Solution {
public:
    vector<int> beautifulArray(int n) {
        vector<int> que = {n};
        vector<vector<int> > sol(n + 1);
        for(int i = 0; i < que.size(); ++i) {
            int u = que[i];
            if(u <= 2)
                continue;
            int lft = u >> 1, rht = u - lft;
            if(que.back() != rht)
                que.push_back(rht);
            if(que.back() != lft)
                que.push_back(lft);
        }
        while(!que.empty()) {
            int u = que.back();
            que.pop_back();
            if(u <= 2) {
                for(int i = 0; i < u; ++i)
                    sol[u].push_back(i);
                continue;
            }
            int lft = u >> 1, rht = u - lft;
            for(int x: sol[lft])
                sol[u].push_back(x << 1 | 1);
            for(int x: sol[rht])
                sol[u].push_back(x << 1);
        }
        for(int &x: sol[n])
            ++x;
        return sol[n];
    }
};
