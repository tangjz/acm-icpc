#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main(){
	int TT,a,b,c,ab,bc,ca;
	scanf("%d",&TT);
	while(TT --){
		scanf("%d%d%d%d%d%d",&a,&b,&c,&ab,&bc,&ca);
		int ret = 0;
		for(int i = 0;i <= a && i <= b;++ i)
			for(int j = 0;j <= b - i && j <= c;++ j){
				int resta = a - i,restc = c - j;
				int r = min(resta,restc);
				if(i * ab + j * bc + r * ca > ret)
					ret = i * ab + j * bc + r * ca;
			}
		printf("%d\n",ret);
	}
}
