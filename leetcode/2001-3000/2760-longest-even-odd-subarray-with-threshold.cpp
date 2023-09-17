class Solution {
public:
    int longestAlternatingSubarray(vector<int>& A, int lim) {
        int n = A.size(), ans = 0;
        auto fix = [&](int &x) {
            return x > lim ? -1 : (x & 1);
        };
        for(int i = 0, j; i < n; ) {
            if(fix(A[i]) != 0) {
                ++i;
                continue;
            }
            for(j = i + 1; j < n && fix(A[j]) == ((j - i) & 1); ++j);
            ans = max(ans, j - i);
            i = j;
        }
        return ans;
    }
};
