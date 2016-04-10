#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXL = 100 + 5;
char buf[MAXL];
int l[MAXL][MAXL],r[MAXL][MAXL],n,m,k;
 
bool chk(int i,int j,int len){
	if(i >= 0 && i < n && j >= 0 && j < m){
		return l[i][j] >= len && r[i][j] >= len;
	}else return true;
}
 
int main(){
	int TT;
	scanf("%d",&TT);
	while(TT --){
		scanf("%d%d%d",&n,&m,&k);
		for(int i = 0;i < n;++ i){
			scanf("%s",buf);
			l[i][0] = buf[0] == 'O';
			for(int j = 1;j < m;++ j)
			if(buf[j] == 'O')
				l[i][j] = l[i][j - 1] + 1;
			else
				l[i][j] = 0;
			r[i][m - 1] = buf[m - 1] == 'O';
			for(int j = m - 2;j >= 0;-- j)
			if(buf[j] == 'O')
				r[i][j] = r[i][j + 1] + 1;
			else
				r[i][j] = 0;
		}
		/*
		for(int i = 0;i < n;++ i,puts(""))
			for(int j = 0;j < m;++ j)
				printf("%d ",l[i][j]);
		*/
		int ret = 0;
		for(int i = k - 1;i < n - k + 1;++ i)
			for(int j = k - 1;j < m - k + 1;++ j)
			if(l[i][j] > 0){
				bool flag = true;
				for(int a = 0;a < k;++ a){
					int ya = i - a,yb = i + a,xlen = k - a;
					if(!chk(ya,j,xlen) || !chk(yb,j,xlen)){
						flag = false; break;
					}
				}
				if(flag) ++ ret;
			}
		printf("%d\n",ret);
	}
	return 0;
}
