class Solution {
public:
    string longestNiceSubstring(string s) {
        static const int maxd = 26;
        pair<int, int> ans = {0, 0};
        vector<int> msk(maxd);
        int n = s.size();
        for(int i = 0; i < n; ++i) {
            int cnt = 0;
            msk.assign(maxd, 0);
            for(int j = i; j < n; ++j) {
                char ch = tolower(s[j]);
                int p = ch - 'a';
                int q = 1 << (s[j] != ch);
                cnt -= msk[p] && msk[p] < 3;
                msk[p] |= q;
                cnt += msk[p] && msk[p] < 3;
                if(!cnt)
                    ans = max(ans, make_pair(j - i + 1, -i));
            }
        }
        return s.substr(-ans.second, ans.first);
    }
};
