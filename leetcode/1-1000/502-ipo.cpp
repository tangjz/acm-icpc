class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = capital.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return capital[u] < capital[v];
        });
        priority_queue<pair<int, int> > que;
        int j = 0;
        for( ; j < n && w >= capital[ord[j]]; ++j)
            que.push({profits[ord[j]], ord[j]});
        for(int i = 0; i < k && !que.empty(); ++i) {
            int u = que.top().second;
            que.pop();
            w += profits[u];
            for( ; j < n && w >= capital[ord[j]]; ++j)
                que.push({profits[ord[j]], ord[j]});
        }
        return w;
    }
};
