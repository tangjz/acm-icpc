#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 100030;
int n,k,p,a[MAXN];

int main(){
	while(scanf("%d%d%d",&n,&k,&p) != EOF){
		long long sum = 0;
		int cnt = 0,cur = 2;
		for(int i = 0;i < n - k;++ i) a[i] = 1;
		cnt = n - k; sum = n - k;
		for(int i = n - k;i < n;++ i){
			if(cnt * 100 < p * i){
				cnt = i; a[i] = ++ cur;
			}else a[i] = cur;
			sum += a[i];
		}
		printf("%I64d\n",sum);
		for(int i = 0;i < n;++ i) printf("%d%c",a[i],i < n - 1 ? ' ' : '\n');
	}
	return 0;
}
