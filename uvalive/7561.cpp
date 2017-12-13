#include <cstdio>
#include <cstring>
const char *buf[] = {"aa", "ab", "ba", "bb"};
int t, n, c[4];
char str[3];
void solve() {
	if(c[0] >= 2) {
		c[0] -= 2;
		printf("%s", buf[0]);
		solve();
		printf("%s", buf[0]);
	} else if(c[1] && c[2]) {
		--c[1];
		--c[2];
		printf("%s", buf[1]);
		solve();
		printf("%s", buf[2]);
	} else if(c[3] >= 2) {
		c[3] -= 2;
		printf("%s", buf[3]);
		solve();
		printf("%s", buf[3]);
	} else if(c[0]) {
		--c[0];
		printf("%s", buf[0]);
	} else if(c[3]) {
		--c[3];
		printf("%s", buf[3]);
	}
}
int main() {
	scanf("%d", &t);
	while(t--) {
		c[0] = c[1] = c[2] = c[3] = 0;
		scanf("%d", &n);
		while(n--) {
			scanf("%s", str);
			c[0] += !strcmp(str, buf[0]);
			c[1] += !strcmp(str, buf[1]);
			c[2] += !strcmp(str, buf[2]);
			c[3] += !strcmp(str, buf[3]);
		}
		solve();
		putchar('\n');
	}
	return 0;
}
