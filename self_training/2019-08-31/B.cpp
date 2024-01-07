#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxd = 101;
int t, len;
LL a, b, c, d;
char buf[maxd];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		c = c - a;
		d = b - d;
		LL tp = a - b;
		if(!tp) {
			if(!c && !d) {
				puts("Yes\n");
			} else {
				puts("No");
			}
			continue;
		}
		if(c % tp != 0 || d % tp != 0) {
			puts("No");
			continue;
		}
		c /= tp;
		d /= tp;
		if(c < 0 || d < 0 || (c & d) || ((c + d) & (c + d + 1))) {
			puts("No");
			continue;
		}
		for(len = 0; c || d; c >>= 1, d >>= 1)
			buf[len++] = "AB"[c & 1];
		buf[len] = '\0';
		puts("Yes");
		puts(buf);
	}
	return 0;
}
