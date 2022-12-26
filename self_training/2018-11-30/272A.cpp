#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
int n, m, len, val;
char buf[maxn];
int main() {
	scanf("%d%d", &n, &m);
	len = max(n, m);
	memset(buf, '0', len * sizeof(char));
	buf[0] = buf[len - 1] = '1';
	for(int i = 0; (i + 1) << 1 < m; ++i) {
		int u = (len >> 1) + i, v = len - 1 - u;
		buf[u] = buf[v] = '1';
	}
//	puts(buf);
	for(int i = len - 1; i >= 0; --i)
		(val = val << 1 | (buf[i] == '1')) >= mod && (val -= mod);
	printf("%d\n", val);
	return 0;
}
