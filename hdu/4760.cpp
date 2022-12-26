#include <cstdio>
typedef unsigned UL;
const int maxn = 1025, maxm = 17;
int sz[maxn], len[maxn][maxm];
UL msk[maxn][maxm];
char buf[maxm];
UL read_ip() {
    UL a, b, c, d;
    scanf("%u.%u.%u.%u", &a, &b, &c, &d);
    return ((a << 8 | b) << 8 | c) << 8 | d;
}
UL read_subnet(int &e) {
    UL a, b, c, d;
    scanf("%u.%u.%u.%u/%d", &a, &b, &c, &d, &e);
    return ((a << 8 | b) << 8 | c) << 8 | d;
}
int main() {
    int id, tp;
    while(scanf("%s", buf) == 1)
        if(buf[0] == 'E') {
            scanf("%d%d", &id, &tp);
            sz[id] = tp;
            int *_len = len[id];
            UL *_msk = msk[id];
            for(int i = 0; i < tp; ++i)
                _msk[i] = read_subnet(_len[i]);
        } else if(buf[0] == 'D') {
            scanf("%d", &id);
            sz[id] = 0;
        } else {
            UL src = read_ip(), dst = read_ip();
            bool chk = 0;
            for(int i = 1; i < maxn && !chk; ++i) {
                if(!sz[i])
                    continue;
                bool schk = 0, dchk = 0;
                int *_len = len[i];
                UL *_msk = msk[i];
                for(int j = 0; j < sz[i]; ++j) {
                    schk |= !((src ^ _msk[j]) >> (32 - _len[j]));
                    dchk |= !((dst ^ _msk[j]) >> (32 - _len[j]));
                }
                chk |= schk & dchk;
            }
            puts(chk ? "F" : "D");
        }
    return 0;
}
