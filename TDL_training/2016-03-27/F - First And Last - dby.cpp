#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
int ans[4][9] = {{17,1,5,105,9,89,149,13,53},
				 {10,18,78,2,102,6,46,106,166},
				 {4,8,88,12,112,16,56,116,156},
				 {7,11,15,115,19,79,159,3,63}}; 

int main(){
	int a,b;
	scanf("%d%d",&a,&b);
	if(a == 1 && b == 1){
		puts("0");
		return 0;
	}
	if(b == 0 || b % 2 == 1)
		puts("-1");
	else
		printf("%d\n",ans[(b >> 1) - 1][a - 1]);
	return 0;
}
