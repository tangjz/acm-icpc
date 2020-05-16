#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int n, s[maxn];
char buf[maxn];
int main() {
	scanf("%d%s", &n, buf);
	for(int i = 0; i < n; ++i)
		s[i + 1] = s[i] + buf[i] - '0';
	if(!s[n]) {
		puts("YES");
		return 0;
	}
	for(int i = 1; i < s[n]; ++i) {
		if(s[n] % i > 0)
			continue;
		bool chk = 1;
		for(int j = 0; chk && s[j] < s[n]; ) {
			int v = s[j] + i;
			for( ; j < n && s[j] < v; ++j);
			chk &= s[j] == v;
		}
		if(chk) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
