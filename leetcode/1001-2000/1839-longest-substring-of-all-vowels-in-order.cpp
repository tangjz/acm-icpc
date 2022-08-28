class Solution {
public:
    int longestBeautifulSubstring(string word) {
        int n = (int)word.size();
        vector<int> nxt(n, n);
        for(int i = n - 2; i >= 0; --i)
            nxt[i] = word[i] == word[i + 1] ? nxt[i + 1] : i + 1;
        const int maxd = 5;
        const char *pat = "aeiou";
        int ans = 0;
        for(int i = 0; i < n; i = nxt[i]) {
            int pos = i, cnt = 0;
            while(cnt < maxd && (pos < n && word[pos] == pat[cnt])) {
                ++cnt;
                pos = nxt[pos];
            }
            if(cnt == maxd)
                ans = max(ans, pos - i);
        }
        return ans;
    }
};
