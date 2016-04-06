#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
char dic[55];
int n;

int main(){
	for(int i = 0;i < 26;++ i) dic[i] = 'a' + i,dic[26 + i] = 'A' + i;
	while(scanf("%d",&n) != EOF){
		printf("%d %d %d\n",2,n,n);
		for(int i = 0;i < n;++ i,puts(""))
			for(int j = 0;j < n;++ j)
				printf("%c",dic[j]);
		puts("");
		for(int i = 0;i < n;++ i,puts(""))
			for(int j = 0;j < n;++ j)
				printf("%c",dic[i]);
	}
	return 0;
}
