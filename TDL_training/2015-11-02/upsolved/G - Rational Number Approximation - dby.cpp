#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a,b,n;

inline ll gcd(ll x,ll y){
	ll tmp;
	while(y){
		tmp = y; y = x % y; x = tmp;
	}
	return x;
}
int main(){
	int cas = 0;
	while(scanf("%lld%lld%lld",&a,&b,&n) != EOF && (a || b || n)){
		ll x1,x3,y1,y3,x2,y2,g;
		g = gcd(a,b);
		a /= g; b /= g;
		printf("Case %d: ",++ cas);
		if(n >= b){
			printf("%lld/%lld %lld/%lld\n",a,b,a,b);
			continue;
		}
		x1 = 0; y1 = 1; x3 = 1; y3 = 1;
		x2 = x1 + x3; y2 = y1 + y3;
		while(y2 <= n){
			if(a * y2 < b * x2)
				x3 = x2,y3 = y2;
			else x1 = x2,y1 = y2;
			x2 = x1 + x3; y2 = y1 + y3;
		}
		printf("%lld/%lld %lld/%lld\n",x1,y1,x3,y3);
	}
	return 0;
}
