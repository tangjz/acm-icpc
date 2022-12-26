#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int MAXL = 103,MAXD = 30;
int mat[MAXL][MAXL],n,m;
char s[MAXL];

int main(){
	int TT;
	scanf("%d",&TT);
	for(int Cas = 1;Cas <= TT;++ Cas){
		printf("Case #%d: ",Cas);
		scanf("%s%d%d",s,&n,&m);
		int len = strlen(s);
		//Step 1
		while(n * m < len){
			if(n < m) n += m;
			else m += n;
		}
		//Step 5
		for(int i = 1;i <= n;++ i)
			for(int j = 1;j <= m;++ j)
				mat[i][j] = -1;
		int lines = len / m,rest = len % m;
		for(int j = m,cur = 0;j;-- j)
			for(int i = 1,lim = (j <= rest) + lines;i <= lim;++ i)
				mat[i][j] = s[cur ++] - 'a';
		//Step 4
		int dt = 1,x = 1,y = 1,ex,ey; lines += rest != 0;
		while(x < lines && mat[x][y] != -1){
			if(y + dt >= 1 && y + dt <= m) ey = y + dt,ex = x;
			else{
				ex = x + 1; ey = y; dt = -dt;
			}
			if(ex == lines || mat[ex][ey] == -1) break;
			int tmp = mat[x][y]; mat[x][y] = mat[ex][ey]; mat[ex][ey] = tmp;
			if(ey + dt >= 1 && ey + dt <= m) y = ey + dt,x = ex;
			else{
				x = ex + 1; y = ey; dt = -dt;
			}
		}
		//Step 3
		for(int i = 1;i <= n && mat[i][1] != -1;++ i)
			for(int j = 1;j <= m && mat[i][j] != -1;++ j)
				mat[i][j] = ((mat[i][j] - i - j) % 26 + 26) % 26;
		//Step 2
		for(int i = 1;i <= n && mat[i][1] != -1;++ i)
			for(int j = 1;j <= m && mat[i][j] != -1;++ j)
				printf("%c",'a' + mat[i][j]);
		puts("");
	}
	return 0;
}
