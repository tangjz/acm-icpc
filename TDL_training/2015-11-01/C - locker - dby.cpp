#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXL = 1005,MAXB = 10,MAXQ = MAXL * MAXB * MAXB * MAXB;
int n;
short f[MAXL][MAXB][MAXB][MAXB];
char s[MAXL],t[MAXL];

struct Info{
	short n,a,b,c;
	inline void ini(int _n,int _a,int _b,int _c){
		n = _n; a = _a; b = _b; c = _c;
	}
}q[MAXQ];

inline int min(int a,int b){return a < b ? a : b;}
void chg(int &nxa,int &nxb,int &nxc,int &nxn,Info now,int dt,int l){
	nxa = (now.a + dt + 10) % 10;
	if(l > 0) nxb = (now.b + dt + 10) % 10;
	if(l > 1) nxc = (now.c + dt + 10) % 10;
	nxn = now.n;
	while(nxa == t[nxn] - '0'){
		nxa = nxb; nxb = nxc; nxc = s[nxn + 3] - '0';
		++ nxn;
	}
}
int main(){
	/*
	freopen("input","r",stdin);
	*/
	while(scanf("%s%s",s,t) != EOF){
		n = strlen(t);	
		int head = 0,tail = 0,nowc,nxn,nxa,nxb,nxc;
		Info now;
		s[n] = '0'; t[n] = '1';
		for(int i = n + 1;i < n + 3;++ i)
			s[i] = t[i] = '0';
		n += 3;
		for(int i = 0;i < n;++ i)
			for(int a = 0;a < 10;++ a)
				for(int b = 0;b < 10;++ b)
					for(int c = 0;c < 10;++ c)
						f[i][a][b][c] = -1;
		int p = 0;
		while(s[p] == t[p]) ++ p;
		if(n - 3 == p){
			puts("0"); continue;
		}
		f[p][s[p] - '0'][s[p + 1] - '0'][s[p + 2] - '0'] = 0;
		q[tail ++].ini(p,s[p] - '0',s[p + 1] - '0',s[p + 2] - '0');
		int ta = s[n - 3] - '0',tb = s[n - 2] - '0',tc = s[n - 1] - '0';
		while(head != tail){
			now = q[head ++];	
			nowc = f[now.n][now.a][now.b][now.c];	
			/*
			printf("%d %d %d %d\n",now.n,now.a,now.b,now.c);
			*/
			for(int i = 2;i >= 0;-- i){
				//Add
				nxa = now.a; nxb = now.b; nxc = now.c;
				chg(nxa,nxb,nxc,nxn,now,1,i);
				if(f[nxn][nxa][nxb][nxc] == -1){
					f[nxn][nxa][nxb][nxc] = nowc + 1;
					q[tail ++].ini(nxn,nxa,nxb,nxc);
				}
				//Sub
				nxa = now.a; nxb = now.b; nxc = now.c;
				chg(nxa,nxb,nxc,nxn,now,-1,i);
				if(f[nxn][nxa][nxb][nxc] == -1){
					f[nxn][nxa][nxb][nxc] = nowc + 1;
					q[tail ++].ini(nxn,nxa,nxb,nxc);
				}
			}
			if(f[n - 3][ta][tb][tc] != -1){
				printf("%d\n",f[n - 3][ta][tb][tc]);
				break;
			}
		}
		/*
		for(int i = 0;i < tail;++ i) printf("f[%d][%d][%d][%d] = %d\n",q[i].n,q[i].a,q[i].b,q[i].c,f[q[i].n][q[i].a][q[i].b][q[i].c]);
		*/
	}
	return 0;
}
