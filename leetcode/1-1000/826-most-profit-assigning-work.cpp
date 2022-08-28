class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int n = profit.size(), m = worker.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return difficulty[u] < difficulty[v];
        });
        sort(worker.begin(), worker.end());
        int ans = 0;
        for(int i = 0, j = 0, upp = 0; i < m; ++i) {
            for( ; j < n && difficulty[ord[j]] <= worker[i]; ++j)
                upp = max(upp, profit[ord[j]]);
            ans += upp;
        }
        return ans;
    }
};
