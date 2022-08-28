class Solution {
public:
    bool isDecomposable(string s) {
        int n = s.size(), cnt = 0;
        for(int i = 0, j; i < n; ) {
            for(j = i; i < n && s[j] == s[i]; ++i);
            int len = i - j;
            if(!cnt && len % 3 >= 2) {
                ++cnt;
                len -= 2;
            }
            if(len % 3 != 0)
                return 0;
        }
        return cnt;
    }
};
