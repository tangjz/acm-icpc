class Solution {
public:
    int stoneGameVI(vector<int>& a, vector<int>& b) {
        int n = a.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            int dt = (a[u] + b[u]) - (a[v] + b[v]);
            return dt > 0 || (!dt && a[u] > a[v]);
        });
        int ans = 0;
        for(int i = 0; i < n; ) {
            // printf("a %d: %d\n", ord[i], a[ord[i]]);
            ans += a[ord[i++]];
            if(i < n) {
                // printf("b %d: %d\n", ord[i], b[ord[i]]);
                ans -= b[ord[i++]];
            }
        }
        return (ans > 0) - (ans < 0);
    }
};
