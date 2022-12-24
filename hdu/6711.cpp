#include <bits/stdc++.h>
using namespace std;
namespace fastIO{
    #define BUF_SIZE 1000000
    #define OUT_SIZE 1000000
    #define ll long long
    //fread->read
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    //fwrite->write
    struct Ostream_fwrite{
        char *buf,*p1,*pend;
        Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
        void out(char ch){
            if (p1==pend){
                fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
            }
            *p1++=ch;
        }
        void println(unsigned x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
            out('\n');
        }
        void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
        ~Ostream_fwrite(){flush();}
    }Ostream;
    inline void println(unsigned x){Ostream.println(x);}
    inline void flush(){Ostream.flush();}
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxv = (int)1e7 + 1, maxe = 9, maxs = maxn << 8 | 1;
int tot, pr[maxv >> 3 | 1], d[maxv];
int t, n, m, sq, a[maxn], b[maxn], pos[maxn], ord[maxn], ans[maxn];
struct Query {
    int L, R;
    bool operator < (Query const &t) const {
        if(pos[L] != pos[t.L])
            return pos[L] < pos[t.L];
        if(pos[L] & 1)
            return R < t.R;
        return R > t.R;
    }
} que[maxn];
int ptot, p[maxe], tail[maxn], seq[maxs];
void dfs(int dep, int val) {
    if(dep == ptot) {
        seq[tot++] = val;
        return;
    }
    dfs(dep + 1, val);
    dfs(dep + 1, -val * p[dep]);
}
int sum0, sum1, cnt[maxv];
void mo_upd(int idx, int sgn) {
    int res = 0, val = a[idx] * sgn;
    for(int i = tail[idx - 1]; i < tail[idx]; ++i) {
        int pos = seq[i];
        if(pos < 0) {
            res -= cnt[-pos];
            cnt[-pos] += val / -pos;
        } else {
            res += cnt[pos];
            cnt[pos] += val / pos;
        }
    }
    sum0 += val * b[idx];
    sum1 += val * (sgn < 0 ? res - b[idx] : res);
    // printf("after %d (%+d): %d %d\n", v, sgn, sum0, sum1);
}
int main() {
    d[1] = 1;
    for(int i = 2; i < maxv; ++i) {
        if(!d[i])
            pr[tot++] = d[i] = i;
        for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
            d[k] = pr[j];
            if(d[i] == pr[j])
                break;
        }
    }
    read(t); // scanf("%d", &t);
    while(t--) {
        read(n), read(m); // scanf("%d%d", &n, &m);
        for(sq = 1; sq * sq <= m; ++sq);
        sq = min(max((int)ceil(n / (sq - 1.0)), 1), n);
        tot = tail[0] = 0;
        for(int i = 1; i <= n; ++i) {
            read(a[i]); // scanf("%d", a + i);
            pos[i] = i <= sq ? 1 : pos[i - sq] + 1;
            int tmp = a[i], &phi = b[i] = tmp;
            for(ptot = 0; tmp > 1; ++ptot) {
                phi -= phi / d[tmp];
                for(int pp = p[ptot] = d[tmp]; d[tmp] == pp; tmp /= pp);
            }
            dfs(0, 1);
            tail[i] = tot;
        }
        for(int i = 1; i <= m; ++i) {
            read(que[i].L), read(que[i].R); // scanf("%d%d", &que[i].L, &que[i].R);
            ord[i] = i;
        }
        sort(ord + 1, ord + m + 1, [&](int const &u, int const &v) {
            return que[u] < que[v];
        });
        int qL = que[ord[1]].L, qR = qL - 1;
        for(int i = 1; i <= m; ++i) {
            int pL = que[ord[i]].L, pR = que[ord[i]].R;
            for( ; qR < pR; ++qR)
                mo_upd(qR + 1, 1);
            for( ; qL > pL; --qL)
                mo_upd(qL - 1, 1);
            for( ; qL < pL; ++qL)
                mo_upd(qL, -1);
            for( ; qR > pR; --qR)
                mo_upd(qR, -1);
            ans[ord[i]] = sum0 + sum1 + sum1;
        }
        for( ; qL <= qR; ++qL)
            mo_upd(qL, -1);
        for(int i = 1; i <= m; ++i)
            println((unsigned)ans[i]); // printf("%u\n", ans[i]);
    }
    return 0;
}