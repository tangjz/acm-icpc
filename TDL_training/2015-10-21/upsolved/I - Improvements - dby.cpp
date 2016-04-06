#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 200030;
int n,a[MAXN],f[MAXN],stk[MAXN];

int main(){
	freopen("improvements.in","r",stdin); freopen("improvements.out","w",stdout);
	while(scanf("%d",&n) != EOF){
		for(int i = 1,x;i <= n;++ i){
			scanf("%d",&x);
			a[x] = i;
		}
		int top = 0;
		for(int i = 1;i <= n;++ i){
			if(top == 0 || stk[top - 1] < a[i]){
				stk[top ++] = a[i];
				f[i] = top;
			}else{
				int p = lower_bound(stk,stk + top,a[i]) - stk;
				stk[p] = a[i];
				f[i] = p + 1;
			}
		}
		top = 0;
		int ret = 0;
		for(int i = n;i;-- i){
			if(top == 0 || stk[top - 1] < a[i]){
				if(top + f[i] > ret) ret = top + f[i];
				stk[top ++] = a[i];
			}else{
				int p = lower_bound(stk,stk + top,a[i]) - stk;
				stk[p] = a[i];
				if(p + f[i] > ret) ret = p + f[i];
			}
		}
		printf("%d\n",ret);
	}
	return 0;
}
