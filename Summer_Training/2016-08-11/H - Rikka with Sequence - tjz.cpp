#include <cmath>
#include <stdio.h>
#include <algorithm>
const int maxn = 100001;
typedef long long LL;
template<class T> inline void scan(T &x)
{
    int ch;
    while((ch = getchar()) < '0' || ch > '9');
    x = ch - '0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch - '0');
}
template<class T> inline void print(T x, char endc = '\n')
{
    int len = 0, num[20];
    while(x)
    {
        num[len++] = x % 10;
        x /= 10;
    }
    if(!len)
        num[len++] = 0;
    while(len)
        putchar('0' + num[--len]);
    putchar(endc);
}
int squ[maxn];
inline LL square_root(LL x)
{
    if(x < maxn)
        return squ[x];
    LL ret = (LL)sqrt(x);
    for( ; ret * ret > x; --ret);
    for( ; (ret + 1) * (ret + 1) <= x; ++ret);
    return ret;
}
int t, n, m;
struct Segment
{
    int size; // size
    LL sum, tag, eqv; //sum, add tag, equal num
} seg[maxn << 1];
inline int seg_idx(int L, int R)
{
    return (L + R) | (L < R);
}
inline void push_down(int rt, int lch, int rch)
{
    if(seg[rt].tag)
    {
        seg[lch].sum += seg[lch].size * seg[rt].tag;
        seg[lch].tag += seg[rt].tag;
        if(seg[lch].eqv)
            seg[lch].eqv += seg[rt].tag;
        seg[rch].sum += seg[rch].size * seg[rt].tag;
        seg[rch].tag += seg[rt].tag;
        if(seg[rch].eqv)
            seg[rch].eqv += seg[rt].tag;
        seg[rt].tag = 0;
    }
    if(seg[rt].eqv && seg[rt].eqv != seg[lch].eqv)
    {
        seg[lch].tag = 0;
        seg[lch].eqv = seg[rt].eqv;
        seg[lch].sum = seg[lch].size * seg[lch].eqv;
        seg[rch].tag = 0;
        seg[rch].eqv = seg[rt].eqv;
        seg[rch].sum = seg[rch].size * seg[rch].eqv;
    }
}
inline void push_up(int rt, int lch, int rch)
{
    seg[rt].sum = seg[lch].sum + seg[rch].sum;
    seg[rt].eqv = seg[lch].eqv == seg[rch].eqv ? seg[lch].eqv : 0;
}
inline void init(int L, int R)
{
    int rt = seg_idx(L, R);
    seg[rt].size = R - L + 1;
    seg[rt].tag = 0;
    if(L == R)
    {
        scan(seg[rt].sum);
        seg[rt].eqv = seg[rt].sum;
        return;
    }
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    init(L, M);
    init(M + 1, R);
    push_up(rt, lch, rch);
}
inline void upd_sum(int L, int R, int l, int r, int x)
{
    int rt = seg_idx(L, R);
    if(l <= L && R <= r)
    {
        seg[rt].sum += (LL)seg[rt].size * x;
        seg[rt].tag += x;
        if(seg[rt].eqv)
            seg[rt].eqv += x;
        return;
    }
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    push_down(rt, lch, rch);
    if(l <= M)
        upd_sum(L, M, l, r, x);
    if(r > M)
        upd_sum(M + 1, R, l, r, x);
    push_up(rt, lch, rch);
}
inline void upd_sqrt(int L, int R, int l, int r)
{
    int rt = seg_idx(L, R);
    if(l <= L && R <= r && seg[rt].eqv)
    {
        seg[rt].tag = 0;
        seg[rt].eqv = square_root(seg[rt].eqv);
        seg[rt].sum = seg[rt].size * seg[rt].eqv;
        return;
    }
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    push_down(rt, lch, rch);
    if(l <= M)
        upd_sqrt(L, M, l, r);
    if(r > M)
        upd_sqrt(M + 1, R, l, r);
    push_up(rt, lch, rch);
}
inline LL query(int L, int R, int l, int r)
{
    int rt = seg_idx(L, R);
    if(l <= L && R <= r)
        return seg[rt].sum;
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    LL ret = 0;
    push_down(rt, lch, rch);
    if(l <= M)
        ret += query(L, M, l, r);
    if(r > M)
        ret += query(M + 1, R, l, r);
    push_up(rt, lch, rch);
    return ret;
}
int main()
{
    for(int i = 1; i * i < maxn; ++i)
        for(int L = i * i, R = std::min((i + 1) * (i + 1), maxn); L < R; ++L)
            squ[L] = i;
    scan(t);
    while(t--)
    {
        scan(n), scan(m);
        init(1, n);
        while(m--)
        {
            int typ, l, r, x;
            scan(typ), scan(l), scan(r);
            if(typ == 1)
            {
                scan(x);
                upd_sum(1, n, l, r, x);
            }
            else if(typ == 2)
                upd_sqrt(1, n, l, r);
            else
                print(query(1, n, l, r));
        }
    }
    return 0;
}
