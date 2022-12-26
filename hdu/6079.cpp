#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxm = 317;
int t, n, m, a[maxn], sqn, blk, fir[maxm + 2], pos[maxn];
int b[maxm][maxm], c[maxm][maxn], p[maxm][maxn], q[maxm][maxn], cnt[maxm + 2], *_cnt;
int modify(int L, int R, int x, int v1, int v2) {
    if(c[x][v1] == c[x - 1][v1])
        return 0;
    if(c[x][v2] == c[x - 1][v2] && L == fir[x] && R == fir[x + 1] - 1) {
        std::swap(q[x][v1], q[x][v2]);
        std::swap(p[x][q[x][v1]], p[x][q[x][v2]]);
        return c[x][v1] - c[x - 1][v1];
    }
    int dt = 0, w = q[x][v2];
    for(int i = L; i <= R; ++i) {
        int v = p[x][a[i]];
        if(v == v1) {
            ++dt;
            a[i] = w;
        }
    }
    return dt;
}
void count1(int L, int R, int x) {
    for(int i = L; i <= R; ++i) {
        int v = p[x][a[i]], y = pos[v];
        ++cnt[y];
    }
}
void count2(int L, int R, int x, int y) {
    for(int i = L; i <= R; ++i) {
        int v = p[x][a[i]];
        if(pos[v] == y)
            ++_cnt[v];
    }
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for(sqn = 1; sqn * sqn < n; ++sqn);
        for(int i = 1, j = 1; i <= n; i += sqn, ++j) {
            int iLim = std::min(i + sqn - 1, n);
            fir[j] = i;
            for(int k = i; k <= iLim; ++k)
                pos[k] = j;
        }
        blk = pos[n];
        fir[blk + 1] = n + 1;
        for(int i = 1; i <= blk; ++i) {
            memset(b[i] + 1, 0, blk * sizeof(int));
            memset(c[i] + 1, 0, n * sizeof(int));
        }
        for(int i = 1; i <= n; ++i) {
            int x = pos[i], v = a[i], y = pos[v];
            ++b[x][y];
            ++c[x][v];
            p[1][i] = q[1][i] = i;
        }
        for(int i = 2; i <= blk; ++i) {
            for(int j = 1; j <= blk; ++j)
                b[i][j] += b[i - 1][j];
            for(int j = 1; j <= n; ++j)
                c[i][j] += c[i - 1][j];
            memcpy(p[i] + 1, p[1] + 1, n * sizeof(int));
            memcpy(q[i] + 1, q[1] + 1, n * sizeof(int));
        }
        while(m--) {
            int typ, L, R, A, B, pL, pR;
            scanf("%d%d%d%d", &typ, &L, &R, &A);
            pL = pos[L];
            pR = pos[R];
            if(typ == 1) {
                scanf("%d", &B);
                if(A == B)
                    continue;
                int pA = pos[A], pB = pos[B];
                if(pL == pR) {
                    int dt = modify(L, R, pL, A, B);
                    if(dt)
                        for(int i = pL; i <= blk; ++i) {
                            b[i][pA] -= dt;
                            b[i][pB] += dt;
                            c[i][A] -= dt;
                            c[i][B] += dt;
                        }
                } else {
                    int dt = 0;
                    for(int i = pL; i <= blk; ++i) {
                        if(dt) {
                            b[i][pA] -= dt;
                            b[i][pB] += dt;
                            c[i][A] -= dt;
                            c[i][B] += dt;
                        }
                        if(i > pR)
                            continue;
                        int res = modify(std::max(L, fir[i]), std::min(R, fir[i + 1] - 1), i, A, B);
                        if(res) {
                            b[i][pA] -= res;
                            b[i][pB] += res;
                            c[i][A] -= res;
                            c[i][B] += res;
                            dt += res;
                        }
                    }
                }
            } else {
                int y, ans;
                memset(cnt + 1, 0, blk * sizeof(int));
                if(fir[pL] < L || R < fir[pR + 1] - 1) {
                    if(pL == pR) {
                        count1(L, R, pL);
                        ++pL;
                    } else {
                        if(fir[pL] < L) {
                            count1(L, fir[pL + 1] - 1, pL);
                            ++pL;
                        }
                        if(R < fir[pR + 1] - 1) {
                            count1(fir[pR], R, pR);
                            --pR;
                        }
                    }
                }
                for(y = 1; y <= blk; ++y) {
                    int ctr = cnt[y] + b[pR][y] - b[pL - 1][y];
                    if(A <= ctr)
                        break;
                    A -= ctr;
                }
                pL = pos[L];
                pR = pos[R];
                _cnt = cnt - fir[y] + 1;
                memset(cnt + 1, 0, sqn * sizeof(int));
                if(fir[pL] < L || R < fir[pR + 1] - 1) {
                    if(pL == pR) {
                        count2(L, R, pL, y);
                        ++pL;
                    } else {
                        if(fir[pL] < L) {
                            count2(L, fir[pL + 1] - 1, pL, y);
                            ++pL;
                        }
                        if(R < fir[pR + 1] - 1) {
                            count2(fir[pR], R, pR, y);
                            --pR;
                        }
                    }
                }
                for(ans = fir[y]; ans < fir[y + 1]; ++ans) {
                    int ctr = _cnt[ans] + c[pR][ans] - c[pL - 1][ans];
                    if(A <= ctr)
                        break;
                    A -= ctr;
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
