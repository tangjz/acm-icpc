#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1;
const DB pi = acos((DB)-1);
int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int lim;
		static char buf[maxn];
		scanf("%d%s", &lim, buf);
		int len = strlen(buf);
		if(len > lim) {
			buf[lim] = buf[lim + 1] = buf[lim + 2] = '.';
			len = lim + 3;
			buf[len] = '\0';
		}
		printf("%s\n", buf);
	}
	return 0;
}