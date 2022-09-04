class Solution {
public:
    int countSegments(string s) {
        int cnt = 0, n = s.size();
        for(int i = 0; i < n; ++i) {
            int sz = 0;
            for( ; i < n && s[i] != ' '; ++i, ++sz);
            cnt += sz > 0;
        }
        return cnt;
    }
};
