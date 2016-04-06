#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
using namespace std;
int n;
int main()
{
	int i;
	scanf("%d",&n);
	if(n % 2 == 0) { printf("-1\n"); return 0; }
	for(i = 0; i < n; ++i) printf("%d ",i);
	printf("\n");
	for(i = 1; i < n; ++i) printf("%d ",i);
	printf("0 \n");
	for(i = 0; i < n - 1; ++i) printf("%d ",(i + i + 1) % n);
	printf("%d \n",n - 1);
	return 0;
}
