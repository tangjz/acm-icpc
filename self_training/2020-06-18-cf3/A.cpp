#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)5e5 + 1;
const int mod = (int)1e9 + 7;


int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		static char buf[maxn];
		scanf("%s", buf);
		int n = strlen(buf), m = 0;
		for(int i = 0; i < n; i += 2)
			buf[m++] = buf[i];
		buf[m++] = buf[n - 1];
		buf[m] = '\0';
		puts(buf);
		// printf("Case #%d:");
	}

	return 0;
}