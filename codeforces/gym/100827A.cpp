#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxl = 25, maxd = 10;

void solve() {
    static char buf[maxl], in[maxl], out[maxl];
    scanf("%s", buf);
    int p1, p2, p3;
    for(p1 = 1; isdigit(buf[p1]) || buf[p1] == '?'; ++p1);
    for(p2 = p1 + 1; buf[p2] != '='; ++p2);
    for(p3 = p2 + 1; buf[p3]; ++p3);
    char op = buf[p1];
    int msk = 0;
    for(int i = 0; i < p3; ++i)
        if(isdigit(buf[i]))
            msk |= 1 << (buf[i] - '0');
    for(int i = 0; i < maxd; ++i, msk >>= 1) {
        if(msk & 1)
            continue;
        for(int j = 0; buf[j]; ++j)
            in[j] = buf[j] == '?' ? '0' + i : buf[j];
        in[p1] = in[p2] = in[p3] = '\0';
        int lft, rht, ret;
        sscanf(in, "%d", &lft);
        sscanf(in + p1 + 1, "%d", &rht);
        sscanf(in + p2 + 1, "%d", &ret);
        sprintf(out, "%d%c%d=%d", lft, op, rht, ret);
        in[p1] = op;
        in[p2] = '=';
        if(strcmp(in, out))
            continue;
        i64 val;
        switch(op) {
            case '+': {
                val = lft + rht;
                break;
            }
            case '-' : {
                val = lft - rht;
                break;
            }
            case '*': {
                val = (i64)lft * rht;
                break;
            }
        }
        if(val != ret)
            continue;
        printf("%d\n", i);
        return;
    }
    puts("-1");
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
