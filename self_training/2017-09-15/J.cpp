#include <bits/stdc++.h>
using namespace std;
const int maxn = 101, maxs = 601;
int t, Case, len, n;
char buf[maxn], str[maxs];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &Case);
		while(getchar() != '\n');
		gets(buf);
		len = strlen(buf);
		scanf("%d", &n);
		for(int i = 0, j = 0, dt; i < n; ++i) {
			scanf("%d", &dt);
			j = (j + dt + len) % len;
			str[i] = buf[j];
		}
		str[n] = '\0';
		printf("%d %s\n", Case, str);
	}
	return 0;
}
