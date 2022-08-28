class Solution {
public:
    unordered_set<int> gen(int num) {
        unordered_set<int> ret;
        ret.insert(num);
        static char s[11], t[11];
        int len = sprintf(s, "%d", num);
        for(char x = '0'; x <= '9'; ++x)
            for(char y = '0'; y <= '9'; ++y) {
                if(x == y)
                    continue;
                for(int i = 0; i < len; ++i)
                    t[i] = s[i] == x ? y : s[i];
                t[len] = '\0';
                if(t[0] == '0')
                    continue;
                int tmp;
                sscanf(t, "%d", &tmp);
                ret.insert(tmp);
            }
        return ret;
    }
    int maxDiff(int num) {
        int mx = num, mn = num;
        for(int x : gen(num)) {
            mx = max(mx, x);
            mn = min(mn, x);
        }
        return mx - mn;
    }
};
