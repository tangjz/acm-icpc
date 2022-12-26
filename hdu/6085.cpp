#include <cstdio>
#include <cstring>
typedef unsigned long long ULL;
const int maxn = 50001, maxm = ((maxn - 1) >> 6) + 1, maxs = 65;
int t, n, m, q, a[maxn], b[maxn], mx1, mx2, c[maxs];
struct Bitset {
    int len;
    ULL data[maxm];
    void reset() {
        memset(data, 0, len * sizeof(ULL));
    }
    void flip(int pos) {
        data[pos >> 6] ^= 1LL << (pos & 63);
    }
    void get(Bitset const &t, int const &L, int const &R) { // [L, R]
        int dx = L >> 6, dy = L & 63, px = R >> 6, py = R & 63;
        reset();
        for(int i = dx; i <= px; ++i) {
            ULL mask = t.data[i];
            if(i == px && py < 63)
                mask &= (1ULL << (py + 1)) - 1;
            data[i - dx] |= mask >> dy;
            if(i > dx && dy > 0)
                data[i - dx - 1] |= mask << (64 - dy);
        }
    }
    void operator ^= (Bitset const &t) {
        for(int i = 0; i < t.len; ++i)
            data[i] ^= t.data[i];
    }
    bool test(int pos) const {
        return (data[pos >> 6] >> (pos & 63)) & 1;
    }
    void print() const {
        for(int i = 0; i < len << 6; ++i)
            putchar(test(i) ? '1' : '0');
        putchar('\n');
    }
} A, B, C;
int main() {
    scanf("%d", &t);
    while(t--) {
        for(int i = 1; i < maxs; ++i)
            c[i] = 0;
        scanf("%d%d%d", &n, &m, &q);
        mx1 = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%d", a + i);
            mx1 < a[i] && (mx1 = a[i]);
        }
        A.len = (mx1 >> 6) + 1;
        A.reset();
        for(int i = 0; i < n; ++i)
            A.flip(a[i]);
        mx2 = 0;
        for(int i = 0; i < m; ++i) {
            scanf("%d", b + i);
            mx2 < b[i] && (mx2 = b[i]);
        }
        B.len = ((mx2 - 1) >> 6) + 1;
        B.reset();
        for(int i = 0; i < m; ++i) {
            if(b[i] < maxs) {
                ++c[b[i]];
                continue;
            }
            C.len = ((b[i] - 1) >> 6) + 1;
            for(int L = 0; L <= mx1; L += b[i]) {
                int R = L + b[i] - 1 < mx1 ? L + b[i] - 1 : mx1;
                C.get(A, L, R);
                B ^= C;
            }
        }
        for(int i = 1; i < maxs; ++i)
            if(c[i] & 1)
                for(int j = 0; j < n; ++j)
                    B.flip(a[j] % i);
        for(int i = 0; i < q; ++i) {
            int x;
            scanf("%d", &x);
            puts(B.test(x) ? "1" : "0");
        }
    }
    return 0;
}
