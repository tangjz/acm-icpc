class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        int n = s.size();
        int r = gcd(n, b), d = gcd(a, 10);
        string ret = s;
        for(int i = 0; i < n; i += r) {
            string t = s.substr(i, n - i) + s.substr(0, i);
            for(int j = 0; j <= (r & 1); ++j) {
                int o = t[!j] - '0';
                int dt = o - o % d;
                for(int k = !j; k < n; k += 2) {
                    int o = t[k] - '0';
                    (o -= dt) < 0 && (o += 10);
                    t[k] = '0' + o;
                }
            }
            ret = min(ret, t);
        }
        return ret;
    }
};
