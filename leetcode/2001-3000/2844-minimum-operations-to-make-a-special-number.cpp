class Solution {
public:
    int minimumOperations(string num) {
        static const int mod = 25, INF = 0x3f3f3f3f;
        static int f[2][mod], cur = 0, pre = 1;
        memset(f[cur], 0x3f, sizeof f[0]);
        f[cur][0] = 0;
        for(char ch: num) {
            int o = ch - '0';
            swap(cur, pre);
            memset(f[cur], 0x3f, sizeof f[0]);
            for(int i = 0; i < mod; ++i) {
                if(f[pre][i] == INF)
                    continue;
                int j = (i * 10 + o) % mod;
                f[cur][i] = min(f[cur][i], f[pre][i] + 1);
                f[cur][j] = min(f[cur][j], f[pre][i]);
            }
        }
        return f[cur][0];
    }
};
