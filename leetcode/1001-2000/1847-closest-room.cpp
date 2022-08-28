class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        int n = rooms.size();
        sort(rooms.begin(), rooms.end());
        vector<int> Log(n + 1);
        Log[0] = -1;
        for(int i = 1; i <= n; ++i)
            Log[i] = Log[i >> 1] + 1;
        vector<vector<int> > st(Log[n] + 1, vector<int>(n));
        for(int i = 0; i < n; ++i)
            st[0][i] = rooms[i][1];
        for(int i = 1; i <= Log[n]; ++i)
            for(int j = 0; j + (1 << i) <= n; ++j)
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        auto ask = [&](int L, int R) { // [L, R]
            if(L > R)
                return 0;
            int d = Log[R - L + 1];
            return max(st[d][L], st[d][R - (1 << d) + 1]);
        };
        int upp = ask(0, n - 1);
        vector<int> ans;
        for(auto &it: queries) {
            if(it[1] > upp) {
                ans.push_back(-1);
                continue;
            }
            int pos = lower_bound(rooms.begin(), rooms.end(), vector<int>{it[0], INT_MAX}) - rooms.begin();
            pair<int, int> res = {INT_MAX, -1};
            if(it[1] <= ask(0, pos - 1)) {
                int pL = 0, pR = pos - 1;
                while(pL < pR) {
                    int pM = (pL + pR + 1) >> 1;
                    if(it[1] <= ask(pM, pos - 1)) {
                        pL = pM;
                    } else {
                        pR = pM - 1;
                    }
                }
                res = min(res, {it[0] - rooms[pL][0], rooms[pL][0]});
            }
            if(it[1] <= ask(pos, n - 1)) {
                int pL = pos, pR = n - 1;
                while(pL < pR) {
                    int pM = (pL + pR) >> 1;
                    if(it[1] <= ask(pos, pM)) {
                        pR = pM;
                    } else {
                        pL = pM + 1;
                    }
                }
                res = min(res, {rooms[pL][0] - it[0], rooms[pL][0]});
            }
            ans.push_back(res.second);
        }
        return ans;
    }
};
