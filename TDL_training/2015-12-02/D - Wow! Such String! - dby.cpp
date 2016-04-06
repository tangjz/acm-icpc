#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXL = 480030,bas = 26 * 26;
char s[MAXL];
int n,len,cur[MAXL],pre[MAXL],ans[MAXL],tot = 0;
bool e[MAXL][30];

void build(){
	s[0] = s[1] = s[2] = 'a';
	//dfs(0,-1);
	int top = 0;
	cur[top] = 0; pre[top ++] = -1;
	bool chk = false;
	while(top){
		int now = cur[top - 1],np = pre[top - 1];
		bool flag = false;
		for(int i = 0;i < 26;++ i)
		if(e[now][i] == 0){
			e[now][i] = 1;
			cur[top] = (now % bas) * 26 + i; pre[top ++] = now;
			if(now * 27 + i == 25 * 27 * 27 * 27) chk = true;
			flag = true; break;
		}
		if(!flag){
			-- top;
			ans[tot ++] = np;
		}
	}
	len = 3;
	for(int i = tot - 3;i >= 0;-- i)
		s[len ++] = (ans[i] % 26) + 'a';
	s[len ++] = 'a';
}
int main(){
	build();
	while(scanf("%d",&n) != EOF){
		if(n > len) puts("Impossible");
		else{
			for(int i = 0;i < n;++ i) printf("%c",s[i]);
			puts("");
		}
	}
	return 0;
}
