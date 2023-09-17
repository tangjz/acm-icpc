class Solution {
public:
    string smallestBeautifulString(string s, int k) {
        int n = s.size();
        for(int i = n - 1; i >= 0; --i) {
            int o = s[i] - 'a';
            for(int j = o + 1; j < k; ++j) {
                if(i > 0 && s[i - 1] - 'a' == j)
                    continue;
                if(i > 1 && s[i - 2] - 'a' == j)
                    continue;
                s[i] = 'a' + j;
                for(int k = i + 1; k < n; ++k) {
                    int u = s[k - 1] - 'a', v = k > 1 ? s[k - 2] - 'a' : -1;
                    int w = !u || !v;
                    w += w == 1 && (u == 1 || v == 1);
                    s[k] = 'a' + w;
                }
                return s;
            }
        }
        return "";
    }
};
