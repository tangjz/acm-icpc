#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main(){
	int n,k;
	while(scanf("%d%d",&n,&k) != EOF){
		int A = 0,B = 0;
		for(int x,i = 0;i < n;++ i){
			scanf("%d",&x);
			if(x > k) A += x - k;
			else B += k - x;
		}
		printf("%d %d\n",A,B);
	}
	return 0;
}
