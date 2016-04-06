#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main(){
	int n,m;
	freopen("alter.in","r",stdin); freopen("alter.out","w",stdout);
	while(scanf("%d%d",&n,&m) != EOF){
		printf("%d\n",n / 2 + m / 2);
		for(int i = 2;i <= n;i += 2)
				printf("%d %d %d %d\n",i,1,i,m);
		for(int j = 2;j <= m;j += 2)
				printf("%d %d %d %d\n",1,j,n,j);
	}
	return 0;
}
