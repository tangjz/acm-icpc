class Solution {
public:
    int minDeletions(string s) {
        const int maxd = 26;
        vector<int> ctr(maxd);
        for(char ch: s)
            ++ctr[(int)(ch - 'a')];
        sort(ctr.begin(), ctr.end());
        int ans = 0;
        for(int i = maxd - 2; i >= 0; --i) {
            int nxt = min(ctr[i], max(ctr[i + 1] - 1, 0));
            ans += ctr[i] - nxt;
            ctr[i] = nxt;
        }
        return ans;
    }
};
