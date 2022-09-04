class Solution {
public:
    int partitionString(string s) {
        static const int maxc = 27;
        int n = s.size(), ans = 0;
        static int st = 0, tim[maxc] = {};
        for(int i = 0; i < n; ++ans) {
            if(!(++st)) {
                memset(tim, 0, sizeof tim);
                ++st;
            }
            for( ; i < n && tim[s[i] - 'a'] != st; tim[s[i++] - 'a'] = st);
        }
        return ans;
    }
};
