class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        int n = plantTime.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return growTime[u] > growTime[v];
        });
        int ans = 0;
        for(int i = 0, c = 0; i < n; ++i) {
            int u = ord[i];
            c += plantTime[u];
            ans = max(ans, c + growTime[u]);
        }
        return ans;
    }
};
