class Solution {
public:
    int countSubstrings(string s) {
        string t = "";
        for(char ch: s) {
            t.push_back('#');
            t.push_back(ch);
        }
        t.push_back('#');
        int ans = 0, m = t.size();
        vector<int> h(m);
        for(int i = 0, L = 0, R = 0; i < m; ++i) {
            h[i] = i < R ? min(h[L + L - i], R - i) : 0;
            for( ; (i - h[i] < 0 ? '?' : t[i - h[i]]) == (i + h[i] < m ? t[i + h[i]] : '!'); ++h[i]);
            if(R < i + h[i]) {
                L = i;
                R = i + h[i];
            }
            ans += h[i] >> 1;
        }
        return ans;
    }
};
