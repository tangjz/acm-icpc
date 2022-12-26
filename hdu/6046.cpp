#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1000, maxm = 1000000;
const int DELTA = 986, SIZE = 7, BLOCKS = (maxm - 1) / DELTA + 1;
const int BITS = SIZE * SIZE, maxs = BLOCKS * BLOCKS;
const LL MASK1 = (1LL << SIZE) - 1, MASK2 = (1LL << BITS) - 1;
int tot, t;
pair<LL, LL> seq[maxs];
LL val[maxn | 1][maxn | 1];
char str[maxn | 1][maxn | 1];
inline int f(int i, int j) {
    LL w = i * (LL)maxm + j;
    unsigned h = 0;
    for(int k = 0; k < 5; ++k) {
        h += w & 255;
        h += h << 10;
        h ^= h >> 6;
        w >>= 8;
    }
    h += h << 3;
    h ^= h >> 11;
    h += h << 15;
    return (h >> 27) & 1;
}
bool test(int x, int y) {
    for(int i = 1, px = x; i <= maxn; ++i, ++px)
        for(int j = 1, py = y; j <= maxn; ++j, ++py)
            if(f(px, py) != (str[i][j] == '1'))
                return 0;
    return 1;
}
int main() {
    for(int i = 1; i <= maxm; i += DELTA)
        for(int j = 1; j <= maxm; j += DELTA) {
            LL msk = 0;
            for(int x = 0; x < SIZE; ++x)
                for(int y = 0; y < SIZE; ++y)
                    msk = msk << 1 | f(i + x, j + y);
            seq[tot++] = make_pair(msk, i * (LL)maxm + j);
        }
    sort(seq, seq + tot);
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        for(int i = 1; i <= maxn; ++i) {
            LL *seq = val[i];
            char *buf = str[i];
            scanf("%s", buf + 1);
            for(int j = 1; j <= maxn; ++j)
                seq[j] = (seq[j - 1] << 1 | (buf[j] == '1')) & MASK1;
        }
        bool chk = 0;
        for(int i = 1; i <= maxn && !chk; ++i)
            for(int j = 1; j <= maxn; ++j) {
                val[i][j] = (val[i - 1][j] << SIZE | val[i][j]) & MASK2;
                if(i < SIZE || j < SIZE)
                    continue;
                int idx = lower_bound(seq, seq + tot, make_pair(val[i][j], 0LL)) - seq;
                if(idx < tot && seq[idx].first == val[i][j]) {
                    LL pos = seq[idx].second;
                    int px = pos / maxm - i + SIZE;
                    int py = pos % maxm - j + SIZE;
                    if(test(px, py)) {
                        chk = 1;
                        printf("Case #%d :%d %d\n", Case, px, py);
                        break;
                    }
                }
            }
    }
    return 0;
}
