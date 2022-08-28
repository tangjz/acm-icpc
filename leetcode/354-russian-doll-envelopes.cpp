class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            int dt = envelopes[u][0] - envelopes[v][0];
            return dt < 0 || (!dt && envelopes[u][1] > envelopes[v][1]);
        });
        vector<int> que;
        for(int u: ord) {
            int p = lower_bound(que.begin(), que.end(), envelopes[u][1]) - que.begin();
            if(p == que.size()) {
                que.push_back(envelopes[u][1]);
            } else {
                que[p] = envelopes[u][1];
            }
        }
        return que.size();
    }
};
