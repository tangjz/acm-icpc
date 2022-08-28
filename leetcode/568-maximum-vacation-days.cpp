class Solution {
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int n = flights.size();
        for(int i = 0; i < n; ++i)
            flights[i][i] = 1;
        vector<int> f(n);
        while(!days[0].empty()) {
            for(int i = 0; i < n; ++i) {
                f[i] += days[i].back();
                days[i].pop_back();
            }
            vector<int> g(n, INT_MIN);
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    if(flights[i][j])
                        g[i] = max(g[i], f[j]);
            f = move(g);
        }
        return f[0];
    }
};
