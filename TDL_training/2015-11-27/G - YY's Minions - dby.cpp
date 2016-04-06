#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int MAXL = 55,MAXK = MAXL * MAXL,dx[] = {-1,-1,0,1,1,1,0,-1},dy[] = {0,1,1,1,0,-1,-1,-1};
int n,m,f,k,x[MAXK],y[MAXK],t[MAXK],ord[MAXK];
char map[2][MAXL][MAXL];

inline bool cmp(int a,int b){
	return t[a] < t[b];
}
int main(){
	int TT;
	scanf("%d",&TT);
	while(TT --){
		scanf("%d%d%d%d",&n,&m,&f,&k);
		int now = 0,last = 1;
		for(int i = 0;i < n;++ i) scanf("%s",map[now][i]);
		for(int i = 0;i < k;++ i) scanf("%d%d%d",&t[i],&x[i],&y[i]),ord[i] = i;
		sort(ord,ord + k,cmp);
		for(int tcur = 1,p = 0;tcur <= f;++ tcur){
			now ^= 1; last ^= 1;
			for(int i = 0;i < n;++ i)
				for(int j = 0;j < m;++ j){
					int awk = 0;
					for(int d = 0;d < 8;++ d){
						int ex = i + dx[d],ey = j + dy[d];
						if(ex >= 0 && ex < n && ey >= 0 && ey < m && map[last][ex][ey] == '1')
								++ awk;
					}
					if(map[last][i][j] == '1'){
						if(awk < 2 || awk > 3) map[now][i][j] = '0';
						else map[now][i][j] = '1';
					}else if(map[last][i][j] == '0'){
						if(awk == 3) map[now][i][j] = '1';
						else map[now][i][j] = '0';
					}else map[now][i][j] = map[last][i][j];
				}
			while(p < k && t[ord[p]] == tcur){
				map[now][x[ord[p]] - 1][y[ord[p]] - 1] = 'X';
				++ p;
			}
		}
		for(int i = 0;i < n;++ i){
			map[now][i][m] = 0;
			printf("%s\n",map[now][i]);
		}
	}
	return 0;
}
