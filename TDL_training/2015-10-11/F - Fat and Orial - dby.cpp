#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
double n,m;
int A,B;

int main(){
	int TT;
	scanf("%d",&TT);
	for(int Cas = 1;Cas <= TT;++ Cas){
		printf("Case #%d: ",Cas);
		scanf("%lf%lf%d%d",&n,&m,&A,&B);
		double ret = m * (A + B) - n * A;
		if(ret < 0 || ret > B * 10.0) puts("Impossible");
		else printf("%.4lf\n",ret / (double)B);
	}
	return 0;
}
