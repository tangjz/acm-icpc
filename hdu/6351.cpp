#include <bits/stdc++.h>
using namespace std;
const int maxn = 9;
int t, n, m, pL[maxn + 2], pR[maxn + 2], qL[maxn], qR[maxn], low, upp;
char buf[maxn + 2];
void dfs(int dep, int cnt, int val) {
    if(dep == n) {
        low = min(low, val);
        upp = max(upp, val);
        return;
    }
    for(int i = pR[n + 1]; i != n; i = pR[i]) {
        pL[pR[i]] = pL[i];
        pR[pL[i]] = pR[i];
        int nxt = cnt + (qR[i] != dep);
        if(nxt <= m) {
            qR[qL[dep]] = qR[i];
            qL[qR[i]] = qL[dep];
            dfs(dep + 1, nxt, (val << 3) + (val << 1) + buf[i]);
            qR[qL[dep]] = dep;
            qL[qR[i]] = i;
        }
        pL[pR[i]] = pR[pL[i]] = i;
    }
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &low, &m);
        upp = low;
        n = sprintf(buf, "%d", low);
        if(n > maxn) {
            printf("%d %d\n", low, upp);
            continue;
        }
        if(n <= m) {
            sort(buf, buf + n, greater<char>());
            sscanf(buf, "%d", &upp);
            for(int i = 1; i < n; ++i)
                if(buf[0] > buf[i] && buf[i] > '0')
                    swap(buf[0], buf[i]);
            sort(buf + 1, buf + n);
            sscanf(buf, "%d", &low);
            printf("%d %d\n", low, upp);
            continue;
        }
        for(int i = 0; i < n; ++i) {
            buf[i] -= '0';
            pL[i] = i - 1;
            pR[i] = i + 1;
            qL[i] = qR[i] = i;
        }
        pL[0] = n + 1;
        pR[n + 1] = 0;
        for(int i = pR[n + 1]; i != n; i = pR[i]) {
            if(!buf[i])
                continue;
            pL[pR[i]] = pL[i];
            pR[pL[i]] = pR[i];
            int cnt = qR[i] != 0;
            if(cnt <= m) {
                qR[qL[0]] = qR[i];
                qL[qR[i]] = qL[0];
                dfs(1, cnt, buf[i]);
                qR[qL[0]] = 0;
                qL[qR[i]] = i;
            }
            pL[pR[i]] = pR[pL[i]] = i;
        }
        printf("%d %d\n", low, upp);
    }
    return 0;
}