class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        const int INF = INT_MAX;
        int n = (int)cars.size(), m = 0;
        vector<double> ans(n);
        vector<int> stk;
        cars.push_back({INF, INF});
        stk.push_back(n);
        ++m;
        auto calc = [&](int u, int v) {
            if(cars[u][1] <= cars[v][1])
                return 1e20;
            // printf("u %d v %d: %f\n", u, v, (cars[v][0] - cars[u][0]) / (double)(cars[v][1] - cars[u][1]));
            return (cars[v][0] - cars[u][0]) / (double)(cars[u][1] - cars[v][1]);
        };
        for(int i = n - 1; i >= 0; --i) {
            while(m > 1 && calc(i, stk[m - 1]) >= calc(i, stk[m - 2])) {
                --m;
            }
            ans[i] = m > 1 ? calc(i, stk[m - 1]) : -1;
            stk.resize(m);
            stk.push_back(i);
            ++m;
        }
        return ans;
    }
};
