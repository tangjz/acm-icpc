#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000001;
int t, Case, mod, ans;
char buf[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%s", &Case, &mod, buf);
		--mod;
		ans = 0;
		for(int i = 0; buf[i]; ++i)
			(ans += buf[i] - '0') >= mod && (ans -= mod);
		printf("%d %d\n", Case, ans);
	}
	return 0;
}
