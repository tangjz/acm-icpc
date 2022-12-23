class Solution {
public:
    int temperatureTrend(vector<int>& A, vector<int>& B) {
        int n = A.size(), ans = 0;
        auto sgn = [&](int x) {
            return (x > 0) - (x < 0);
        };
        for(int i = 0; i < n; ++i) {
            int cnt = 0;
            for( ; i + 1 < n && sgn(A[i] - A[i + 1]) == sgn(B[i] - B[i + 1]); ++i, ++cnt);
            ans = max(ans, cnt);
        }
        return ans;
    }
};
