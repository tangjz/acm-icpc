class Solution {
public:
    string splitLoopedString(vector<string>& strs) {
        string ans = "";
        int n = strs.size();
        for(string &buf: strs) {
            string rev = buf;
            reverse(rev.begin(), rev.end());
            if(buf < rev)
                buf = rev;
        }
        for(int i = 0; i < n; ++i)
            for(int turn = 0; turn < 2; ++turn) {
                string rem = "";
                for(int j = (i + 1) % n; j != i; (++j) == n && (j = 0))
                    rem += strs[j];
                for(int j = 0; j < (int)strs[i].size(); ++j) {
                    string cur = strs[i].substr(j) + rem + strs[i].substr(0, j);
                    ans = max(ans, cur);
                }
                reverse(strs[i].begin(), strs[i].end());
            }
        return ans;
    }
};
