#include <vector>
#include <stdio.h>
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
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;
typedef long long LL;
const int maxn = 500001;
int n, m, r, a[maxn], b[maxn], szN, szM, fir[maxn], pos[maxn];
LL q;
vector<int> seq[maxn], s[3][maxn];
int main()
{
	read(n), read(m), read(q);
	r = __gcd(n, m);
	szN = n / r;
	szM = m / r;
	for(int i = 0; i < n; ++i)
		read(a[i]);
	for(int i = 0; i < m; ++i)
		read(b[i]);
	for(int i = 0; i < r; ++i)
	{
		for(int j = 0, id = i; j < szM; ++j, id = (id + n) % m)
		{
			pos[id] = j;
			seq[i].push_back(b[id]);
		}
		for(int j = 0, id1 = i, id2 = i; j < szN; ++j, id1 += r, id2 = id2 + r < m ? id2 + r : id2 + r - m)
			fir[id1] = pos[id2];
	}
	for(int v = 0; v < 3; ++v)
		for(int i = 0; i < r; ++i)
		{
			int tp = 0;
			s[v][i].push_back(tp);
			for(int j = 0; j < szM; ++j)
			{
				tp += seq[i][j] == v;
				s[v][i].push_back(tp);
			}
			for(int j = 0; j < szM; ++j)
			{
				tp += seq[i][j] == v;
				s[v][i].push_back(tp);
			}
		}
	LL cntA = 0, cntB = 0;
	for(int i = 0, j = 0; i < n; ++i, j = j + 1 < r ? j + 1 : 0)
	{
		if(q <= i)
			continue;
		LL cnt = (q - i - 1) / n + 1;
		LL tot = cnt / szM;
		int res = cnt % szM;
		int win = (a[i] + 1) % 3, lose = (a[i] + 2) % 3;
		cntA += s[win][j][szM] * tot;
		cntB += s[lose][j][szM] * tot;
		if(res)
		{
			cntA += s[win][j][fir[i] + res] - s[win][j][fir[i]];
			cntB += s[lose][j][fir[i] + res] - s[lose][j][fir[i]];
		}
	}
	printf("%lld %lld\n", cntA, cntB);
	return 0;
}
