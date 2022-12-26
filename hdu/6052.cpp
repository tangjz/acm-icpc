#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 101, maxm = 10001;
int t, n, m, all, cnt, pos[maxn], stk[maxn][2];
long long ans;
vector<pair<int, int> > e[maxm];
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n * m; ++i)
            vector<pair<int, int> >().swap(e[i]);
        all = ((n * (n + 1)) >> 1) * ((m * (m + 1)) >> 1);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                int col;
                scanf("%d", &col);
                e[col].push_back(make_pair(i, j));
            }
        ans = 0;
        for(int o = 0; o < n * m; ++o) {
            if(!e[o].size())
                continue;
            int x = e[o][0].first;
            cnt = ((x * (x + 1)) >> 1) * (m * (m + 1) >> 1);
            memset(pos, -1, m * sizeof(int));
            // printf("col %d\n", o);
            for(int i = 0, sz = (int)e[o].size(); i < sz; ) {
                int x = e[o][i].first;
                for( ; i < sz && e[o][i].first == x; ++i)
                    pos[e[o][i].second] = x;
                int sum = 0, ctr = 0, top = -1;
                for(int j = 0; j < m; ++j) {
                    int w = 1, h = x - pos[j];
                    for( ; top >= 0 && stk[top][1] >= h; --top) {
                        ctr -= stk[top][0] * stk[top][1];
                        w += stk[top][0];
                    }
                    stk[++top][0] = w;
                    stk[top][1] = h;
                    ctr += w * h;
                    sum += ctr;
                }
                // printf("row %d: %d\n", x, sum);
                int coeff = (i < sz ? e[o][i].first : n) - x;
                cnt += coeff * sum + ((coeff * (coeff - 1)) >> 1) * ((m * (m + 1)) >> 1);
            }
            // printf("total: %d\n", cnt);
            ans += all - cnt;
        }
        printf("%.9f\n", ans / (double)all);
    }
    return 0;
}
