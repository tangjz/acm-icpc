#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
const int MAXN = 100000 + 5;
char buf[MAXN];
 
int main(){
	int TT;
	scanf("%d",&TT);
	while(TT --){
		int n;
		scanf("%d",&n);
		scanf("%s",buf);
		int cnt = 0;
		for(int i = 0;i < n;++ i)
			cnt += buf[i] == '1';
		for(int i = 0;i < cnt;++ i)
			printf("1");
		puts("");
	}
	return 0;
}
