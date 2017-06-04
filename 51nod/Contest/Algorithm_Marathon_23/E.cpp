#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
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
    //getchar->read
    inline void read1(int &x){
        char ch;int bo=0;x=0;
        for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
        for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
        if (bo)x=-x;
    }
    inline void read1(ll &x){
        char ch;int bo=0;x=0;
        for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
        for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
        if (bo)x=-x;
    }
    inline void read1(double &x){
        char ch;int bo=0;x=0;
        for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
        for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
        if (ch=='.'){
            double tmp=1;
            for (ch=getchar();ch>='0'&&ch<='9';tmp/=10.0,x+=tmp*(ch-'0'),ch=getchar());
        }
        if (bo)x=-x;
    }
    inline void read1(char *s){
        char ch=getchar();
        for (;blank(ch);ch=getchar());
        for (;!blank(ch);ch=getchar())*s++=ch;
        *s=0;
    }
    inline void read1(char &c){for (c=getchar();blank(c);c=getchar());}
    //scanf->read
    inline void read2(int &x){scanf("%d",&x);}
    inline void read2(ll &x){
        #ifdef _WIN32
            scanf("%I64d",&x);
        #else
        #ifdef __linux
            scanf("%lld",&x);
        #else
            puts("error:can't recognize the system!");
        #endif
        #endif
    }
    inline void read2(double &x){scanf("%lf",&x);}
    inline void read2(char *s){scanf("%s",s);}
    inline void read2(char &c){scanf(" %c",&c);}
    inline void readln2(char *s){gets(s);}
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
    //puts->write
    char Out[OUT_SIZE],*o=Out;
    inline void print1(int x){
        static char buf[15];
        char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
        while(x)*p1++=x%10+'0',x/=10;
        while(p1--!=buf)*o++=*p1;
    }
    inline void println1(int x){print1(x);*o++='\n';}
    inline void print1(ll x){
        static char buf[25];
        char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
        while(x)*p1++=x%10+'0',x/=10;
        while(p1--!=buf)*o++=*p1;
    }
    inline void println1(ll x){print1(x);*o++='\n';}
    inline void print1(char c){*o++=c;}
    inline void println1(char c){*o++=c;*o++='\n';}
    inline void print1(char *s){while (*s)*o++=*s++;}
    inline void println1(char *s){print1(s);*o++='\n';}
    inline void println1(){*o++='\n';}
    inline void flush1(){if (o!=Out){if (*(o-1)=='\n')*--o=0;puts(Out);}}
    struct puts_write{
        ~puts_write(){flush1();}
    }_puts;
    inline void print2(int x){printf("%d",x);}
    inline void println2(int x){printf("%d\n",x);}
    inline void print2(char x){printf("%c",x);}
    inline void println2(char x){printf("%c\n",x);}
    inline void print2(ll x){
        #ifdef _WIN32
            printf("%I64d",x);
        #else
        #ifdef __linux
            printf("%lld",x);
        #else
            puts("error:can't recognize the system!");
        #endif
        #endif
    }
    inline void println2(ll x){print2(x);printf("\n");}
    inline void println2(){printf("\n");}
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;
typedef long long LL;
const int maxn = 50001;
int n, q, a[maxn], tot, que[maxn], lpos[maxn];
LL bit[4][maxn], ans[maxn];
struct Query {
	int idx, L, R;
	void read(int id) {
		idx = id;
		::read(L), ::read(R); //scanf("%d%d", &L, &R);
	}
	bool operator < (Query const &t) const {
		if(lpos[L] != lpos[t.L])
			return lpos[L] < lpos[t.L];
		return R < t.R;
	}
} query[maxn];
inline void mod_inc(LL &x, LL y)
{
	x += y;
}
inline void mod_dec(LL &x, LL y)
{
	x -= y;
}
void upd(int pos, int x, int y, int v)
{
	LL xy = (LL)x * y;
	void (*oper)(LL &, LL) = v > 0 ? mod_inc : mod_dec;
	for( ; pos <= tot; pos += pos & -pos)
	{
		oper(bit[0][pos], 1);
		oper(bit[1][pos], x);
		oper(bit[2][pos], y);
		oper(bit[3][pos], xy);
	}
}
LL sum(int pos, int x, int y) // return (a[j] - a[i]) * (j - i)
{
	LL ret[4] = {};
	for( ; pos > 0; pos -= pos & -pos)
	{
		mod_inc(ret[0], bit[0][pos]);
		mod_inc(ret[1], bit[1][pos]);
		mod_inc(ret[2], bit[2][pos]);
		mod_inc(ret[3], bit[3][pos]);
	}
	return ret[0] * x * y - ret[1] * y - ret[2] * x + ret[3];
}
int main()
{
	read(n); //scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		read(a[i]); //scanf("%d", a + i);
	memcpy(que + 1, a + 1, n * sizeof(int));
	sort(que + 1, que + n + 1);
	tot = unique(que + 1, que + n + 1) - que - 1;
	int sqn = (int)ceil(sqrt(n << 2) + 9);
	for(int i = 1, j = 1; i <= n; ((i++) % sqn) || ++j)
	{
		lpos[i] = j;
		a[i] = lower_bound(que + 1, que + tot + 1, a[i]) - que;
	}
	read(q); //scanf("%d", &q);
	for(int i = 1; i <= q; ++i)
		query[i].read(i);
	sort(query + 1, query + q + 1);
	LL res = 0;
	for(int i = 1, L = 1, R = 0; i <= q; ++i)
	{
		while(R < query[i].R)
		{
			++R;
			if(a[R] < tot)
				res -= sum(tot, R, que[a[R]]) - sum(a[R], R, que[a[R]]);
			if(a[R] > 1)
				res += sum(a[R] - 1, R, que[a[R]]);
			upd(a[R], R, que[a[R]], 1);
		}
		while(L > query[i].L)
		{
			--L;
			if(a[L] < tot)
				res += sum(tot, L, que[a[L]]) - sum(a[L], L, que[a[L]]);
			if(a[L] > 1)
				res -= sum(a[L] - 1, L, que[a[L]]);
			upd(a[L], L, que[a[L]], 1);
		}
		while(L < query[i].L)
		{
			upd(a[L], L, que[a[L]], -1);
			if(a[L] < tot)
				res -= sum(tot, L, que[a[L]]) - sum(a[L], L, que[a[L]]);
			if(a[L] > 1)
				res += sum(a[L] - 1, L, que[a[L]]);
			++L;
		}
		while(R > query[i].R)
		{
			upd(a[R], R, que[a[R]], -1);
			if(a[R] < tot)
				res += sum(tot, R, que[a[R]]) - sum(a[R], R, que[a[R]]);
			if(a[R] > 1)
				res -= sum(a[R] - 1, R, que[a[R]]);
			--R;
		}
		ans[query[i].idx] = res;
	}
	for(int i = 1; i <= q; ++i)
	{
		static char buf[1 << 5 | 1];
		sprintf(buf, "%llu", ans[i]);
		println(buf);
	}
	return 0;
}
