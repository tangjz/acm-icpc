class Solution {
public:
    vector<int> analysisHistogram(vector<int>& A, int cnt) {
        int n = A.size(), ans = INT_MAX, pos = -1;
        sort(A.begin(), A.end());
        for(int i = 0; i <= n - cnt; ++i) {
            int dt = A[i + cnt - 1] - A[i];
            if(dt < ans) {
                ans = dt;
                pos = i;
            }
        }
        rotate(A.begin(), A.begin() + pos, A.end());
        A.resize(cnt);
        return A;
    }
};
