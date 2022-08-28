class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        if(!m)
            return 0;
        if(n < m)
            return -1;
        vector<int> nxt(m + 1);
        for(int i = 1, j = 0; i < m; ++i) {
            for( ; j && needle[i] != needle[j]; j = nxt[j]);
            nxt[i + 1] = needle[i] == needle[j] ? (++j) : 0;
        }
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j && haystack[i] != needle[j]; j = nxt[j]);
            j += haystack[i] == needle[j];
            if(j == m)
                return i - m + 1;
        }
        return -1;
    }
};
