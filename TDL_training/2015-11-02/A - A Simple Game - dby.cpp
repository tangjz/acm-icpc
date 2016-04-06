#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXN = 30030;
int neg[MAXN],pos[MAXN],n,T;

inline int gcd(int x,int y){
	int tmp;
	while(y){
		tmp = y; y = x % y; x = tmp;	
	}
	return x;
}
int main(){
	int cnt = 0;
	while(scanf("%d%d",&n,&T) != EOF && (n != 0 || T != 0)){
		int cneg = 0,cpos = 0;
		for(int x,i = 0;i < n;++ i){
			scanf("%d",&x);
			if(x <= 0) neg[cneg ++] = x;
			else pos[cpos ++] = x;
		}
		sort(pos,pos + cpos);
		sort(neg,neg + cneg);
		int B = n * n,A = 0;
		int rp = cpos,rn = 0; 
		for(int i = 0;i < cpos;++ i){
			while(rp - 1 >= 0 && pos[rp - 1] * pos[i] > T) -- rp;
			while(rn < cneg && neg[rn] * pos[i] <= T) ++ rn;
			A += cpos - rp + cneg - rn;
		}
		rp = 0; rn = cneg;
		for(int i = 0;i < cneg;++ i){
			while(rp < cpos && pos[rp] * neg[i] > T) ++ rp;
			while(rn - 1 >= 0 && neg[rn - 1] * neg[i] <= T) -- rn;
			A += rp + rn;
		}
		int g = gcd(A,B);
		printf("Case %d: %d/%d\n",++ cnt,A / g,B / g);
	}
	return 0;
}
