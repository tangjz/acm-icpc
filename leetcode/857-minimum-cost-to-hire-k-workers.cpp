class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        // min max(unit) * sum(weight)
        // s.t. cnt = K
        int n = (int)wage.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return wage[u] * quality[v] < wage[v] * quality[u];
        });
        typedef long long LL;
        double ans = 1e20;
        LL sum = 0;
        priority_queue<int> que;
        for(int i = 1; i <= n; ++i) {
            int u = ord[i - 1];
            sum += quality[u];
            que.push(quality[u]);
            if(i < K)
                continue;
            if(i > K) {
                sum -= que.top();
                que.pop();
            }
            ans = min(ans, sum * wage[u] / (double)quality[u]);
        }
        return ans;
    }
};
