class Solution {
public:
    int minimumKeypresses(string s) {
        static const int maxd = 26, maxn = 9;
        vector<int> ctr(maxd);
        for(char ch: s)
            ++ctr[(int)(ch - 'a')];
        sort(ctr.begin(), ctr.end());
        int ans = 0;
        for(int i = 0; i < maxd && ctr.back(); ++i) {
            ans += ctr.back() * (i / maxn + 1);
            ctr.pop_back();
        }
        return ans;
    }
};
