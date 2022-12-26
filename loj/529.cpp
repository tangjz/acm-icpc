#include <cstdio>
const int maxn = 1000001;
int t;
char buf[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%s", buf);
		bool ban = 0, chk = buf[0] == 'N';
		for(int i = 1; !ban && buf[i]; ++i) {
			ban |= buf[i - 1] == 'N' && buf[i] == 'N';
			chk |= buf[i] == 'N';
		}
		ban |= !chk;
		if(ban)
			puts("0 0");
		else if(buf[0] != 'N')
			puts("1 0");
		else
			puts("1 1");
	}
	return 0;
}
