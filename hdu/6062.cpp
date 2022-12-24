#include <cstdio>
//#include <cassert>
const int maxn = 8001, maxm = 8001;
int n, m, msk[2][maxm], val[maxm], in[maxn], out, ONE, ONE2, ZERO, not_in[maxn], seq[2][maxm], cur, pre = 1, res[maxm];
int tot, op[maxm][3];
void addOp(int a, int b, int c) {
    op[++tot][0] = a;
    op[tot][1] = b;
    op[tot][2] = c;
}
int main() {
    while(scanf("%d", &n) == 1) {
        msk[0][0] = msk[1][0] = 0;
        for(int i = 0; i < 1 << n; ++i) {
            int mask = 0, x;
            static char str[maxn];
            scanf("%s", str);
            for(int j = 0; j < n; ++j)
                mask = (mask << 1) | (str[j] == '1');
            scanf("%d", &x);
            msk[x][++msk[x][0]] = mask;
        }
        int need = msk[0][0] < msk[1][0] ? 0 : 1;
        m = tot = 0;
        for(int i = 1; i <= n; ++i)
            in[i] = ++m;
        out = ++m;
        val[m] = need;
        ONE = ++m;
        val[m] = 1;
        ONE2 = ++m;
        val[m] = 1;
        ZERO = ++m;
        val[m] = 0;
        for(int i = 1; i <= n; ++i) {
            not_in[i] = ++m;
            val[m] = 1;
            addOp(in[i], ONE, not_in[i]);
        }
        seq[cur][0] = ONE;
        for(int i = 1; i <= n; ++i) {
            pre ^= 1;
            cur ^= 1;
            for(int j = 0; j < 1 << i; ++j) {
                seq[cur][j] = ++m;
                val[m] = 0;
                addOp(seq[pre][j >> 1], ((j & 1) ? in[i] : not_in[i]), seq[cur][j]);
            }
        }
        res[0] = ONE;
        int len = msk[need][0];
        for(int i = 1; i <= len; ++i) {
            res[i] = ++m;
            val[m] = 0;
            int mask = msk[need][i];
            addOp(ONE, ONE2, seq[cur][mask]);
            addOp(res[i - 1], seq[cur][mask], res[i]);
        }
        addOp(res[len], ONE2, out);
        //assert(val[out] == 0 || val[out] == 1);
        printf("%d\n", val[out]);
        //assert(m - n - 1 >= 0 && m - n - 1 <= 800);
        printf("%d\n", m - n - 1);
        for(int i = n + 2; i <= m; ++i) {
            //assert(val[i] == 0 || val[i] == 1);
            printf("%d\n", val[i]);
        }
        //assert(tot >= 0 && tot <= 800);
        printf("%d\n", tot);
        for(int i = 1; i <= tot; ++i) {
            //assert(1 <= op[i][0] && op[i][0] <= m);
            //assert(1 <= op[i][1] && op[i][1] <= m);
            //assert(1 <= op[i][2] && op[i][2] <= m);
            //assert(op[i][0] != op[i][1] && op[i][0] != op[i][2] && op[i][1] != op[i][2]);
            printf("%d %d %d\n", op[i][0], op[i][1], op[i][2]);
        }
    }
    return 0;
}