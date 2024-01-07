#include <bits/stdc++.h>
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
		}
		return *p1++;
	}
	inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	template<class T>
	inline void read(T &x){
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
		void print(ll x){
			static char s[25],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)out('-'),x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1);
		}
		void print(char *s){while (*s)out(*s++);}
		void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
		~Ostream_fwrite(){flush();}
	}Ostream;
	inline void print(ll x){Ostream.print(x);}
	inline void print(char *s){Ostream.print(s);}
	inline void flush(){Ostream.flush();}
	#undef ll
	#undef OUT_SIZE
	#undef BUF_SIZE
};
using namespace fastIO;
typedef long long LL;
const int maxn = 11, coeff[maxn] = {1, 1, 0, -1, -1, 0, -1, -1, 0, 1, 1}, row[maxn] = {0, 1, 1, 0, 3, 0, 3, 5, 4, 1, 9};
int t;
LL m, f[2][maxn], deg[2], vec[maxn << 1 | 1];
inline void poly_mod() {
	for(int i = deg[0] - deg[1]; i >= 0; --i) {
		if(!vec[i + deg[1]])
			continue;
		LL d = vec[i + deg[1]];
		for(int j = 0; j <= deg[1]; ++j)
			vec[i + j] -= d * f[1][j];
	}
	for( ; deg[0] && !vec[deg[0]]; --deg[0]);
	for(int i = 0; i <= deg[0]; ++i)
		f[0][i] = vec[i];
}
int main() {
	read(t);
	while(t--) {
		read(m);
		deg[0] = 0;
		f[0][0] = 1;
		deg[1] = maxn - 1;
		for(int i = 0; i <= deg[1]; ++i)
			f[1][i] = coeff[i];
		int mx = 0;
		for( ; (1LL << mx) <= m; ++mx);
		for(int i = mx - 1; i >= 0; --i) {
			memset(vec, 0, (deg[0] << 1 | 1) * sizeof(LL));
			for(int j = 0; j <= deg[0]; ++j)
				for(int k = 0; k <= deg[0]; ++k)
					vec[j + k] += f[0][j] * f[0][k];
			deg[0] <<= 1;
			poly_mod();
			if((m >> i) & 1) {
				vec[0] = 0;
				for(int j = 0; j <= deg[0]; ++j)
					vec[j + 1] = f[0][j];
				++deg[0];
				poly_mod();
			}
		}
		LL ans = 0;
		for(int i = 0; i <= deg[0]; ++i)
			ans += f[0][i] * row[i];
		print(ans);
		print("\n");
	}
	return 0;
}
