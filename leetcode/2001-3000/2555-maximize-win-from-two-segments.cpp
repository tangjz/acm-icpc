class Solution {
public:
    int maximizeWin(vector<int>& seq, int k) {
        int n = seq.size();
        vector<int> pre(n);
        sort(seq.begin(), seq.end());
        for(int i = 0, j = 0, upp = 0; i < n; ++i) {
            for( ; j < i && seq[i] - seq[j] > k; ++j);
            pre[i] = upp = max(upp, i - j + 1);
        }
        int ans = 0;
        for(int i = n - 1, j = n - 1; i >= 0; --i) {
            for( ; j > i && seq[j] - seq[i] > k; --j);
            ans = max(ans, (i ? pre[i - 1] : 0) + (j - i + 1));
        }
        return ans;
    }
};
