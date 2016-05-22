#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 5;
long long dp[MAXN][2];
int c[MAXN],f[MAXN],n;

inline void upd(long long &x,long long y){
	if(x == -1) x = y;
	else if(x > y) x = y;
}

int main(){
	scanf("%d",&n);
	for(int i = 0;i < n;++ i) scanf("%d",&c[i]);
	for(int i = 0;i < n;++ i) scanf("%d",&f[i]);
 	memset(dp,-1,sizeof(dp));
	dp[0][0] = 0;
	dp[0][1] = c[0] - f[0];
	for(int i = 1;i < n;++ i){
		for(int j = 0;j < 2;++ j)
		if(dp[i - 1][j] != -1){
			int p = j == 0 ? f[i - 1] + 1 : c[i - 1];
			if(p > f[i] && p <= c[i]) upd(dp[i][j],dp[i - 1][j]);
		}
		if(dp[i][0] != -1) upd(dp[i][1],dp[i][0] + c[i] - f[i]);
		if(dp[i][1] != -1) upd(dp[i][0],dp[i][1] + c[i] - f[i]);
	}
	/*
	for(int i = 0;i < n;++ i)
		printf("0:%lld  1:%lld\n",dp[i][0],dp[i][1]);
	*/
	printf("%lld\n",dp[n - 1][0]);
	return 0;
}
