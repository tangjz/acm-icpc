class Solution {
public:
    string robotWithString(string s) {
        int n = s.size();
        string p = s, t, ans;
        for(int i = n - 1; i > 0; --i)
            p[i - 1] = min(p[i - 1], p[i]);
        for(int i = 0, j = 0; i < n; ++i)
            if(t.empty() || (j < n && t.back() > p[j])) {
                for( ; j < n && p[j] != s[j]; ++j)
                    t.push_back(s[j]);
                ans.push_back(s[j++]);
            } else {
                ans.push_back(t.back());
                t.pop_back();
            }
        return ans;
    }
};
