#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    //fread->read
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
            //{printf("IO error!\n");system("pause");for (;;);exit(0);}
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
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(double &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (ch=='.'){
            double tmp=1; ch=nc();
            for (;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
        }
        if (sign)x=-x;
    }
    inline void read(char *s){
        char ch=nc();
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        for (;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
        *s=0;
    }
    inline void read(char &c){
        for (c=nc();blank(c);c=nc());
        if (IOerror){c=-1;return;}
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
        void print(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void println(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1); out('\n');
        }
        void print(ll x){
            static char s[25],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void println(ll x){
            static char s[25],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1); out('\n');
        }
        void print(char *s){while (*s)out(*s++);}
        void println(char *s){while (*s)out(*s++);out('\n');}
        void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
        ~Ostream_fwrite(){flush();}
    }Ostream;
    inline void print(int x){Ostream.print(x);}
    inline void println(int x){Ostream.println(x);}
    inline void print(char x){Ostream.out(x);}
    inline void println(char x){Ostream.out(x);Ostream.out('\n');}
    inline void print(ll x){Ostream.print(x);}
    inline void println(ll x){Ostream.println(x);}
    inline void print(char *s){Ostream.print(s);}
    inline void println(char *s){Ostream.println(s);}
    inline void println(){Ostream.out('\n');}
    inline void flush(){Ostream.flush();}
};
using namespace fastIO;
typedef long long LL;
const int maxn = 100001;
int n, m, C, x[maxn], y[maxn], p[maxn], ord[maxn], ans;
int sz, bit[maxn];
LL que[maxn];
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
void update(int x, int v)
{
	for( ; x <= sz; x += x & -x)
		upd(bit[x], v);
}
int query(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		upd(ret, bit[x]);
	return ret;
}
void solve()
{
	for(int i = 0, j = 0; i < m; i = j)
	{
		sz = 0;
		for(int dt = x[ord[i]] - y[ord[i]]; j < m && x[ord[j]] - y[ord[j]] == dt; ++j)
			que[sz++] = (LL)p[ord[j]] * p[ord[j]] + x[ord[j]];
		sort(que, que + sz);
		sz = unique(que, que + sz) - que;
		memset(bit + 1, 0, sz * sizeof(int));
		que[sz] = (LL)1e15;
		for(int k = i; k < j; ++k)
		{
			LL lim = x[ord[k]] - (LL)p[ord[k]] * p[ord[k]] - C + 1;
			int idx = upper_bound(que, que + sz + 1, lim) - que;
			int val = query(idx) + 1;
			lim = (LL)p[ord[k]] * p[ord[k]] + x[ord[k]];
			idx = lower_bound(que, que + sz, lim) - que + 1;
			update(idx, val);
			upd(ans, val);
		}
	}
}
bool cmp(const int &a, const int &b)
{
	int da = x[a] - y[a], db = x[b] - y[b];
	if(da != db)
		return da < db;
	return x[a] < x[b];
}
int main()
{
	freopen("bishops.in", "r", stdin);
	int t;
	read(t);
	while(t--)
	{
		ans = 0;
		read(n), read(m), read(C);
		assert(0 < n && n <= 100000);
		assert(0 < m && m <= 100000);
		assert(0 <= C && C <= 100000);
		for(int i = 0; i < m; ++i)
		{
			read(x[i]), read(y[i]), read(p[i]);
			assert(1 <= x[i] && x[i] <= n);
			assert(1 <= y[i] && y[i] <= n);
			assert(1 <= p[i] && p[i] <= n);
			ord[i] = i;
		}
		sort(ord, ord + m, cmp);
		solve();
		for(int i = 0; i < m; ++i)
		{
			swap(x[i], y[i]);
			x[i] = -x[i];
		}
		sort(ord, ord + m, cmp);
		solve();
		println(ans);
	}
	return 0;
}
