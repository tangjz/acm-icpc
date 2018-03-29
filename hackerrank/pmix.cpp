#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int n, m, cur, pre = 1;
char buf[2][maxn];
int main() {
	scanf("%d%d%s", &n, &m, buf[cur]);
	for(int i = 0; i < n; ++i)
		buf[cur][i] -= 'A';
	for(int i = 1; i <= m; i <<= 1) {
		if(!(m & i))
			continue;
		pre ^= 1;
		cur ^= 1;
		for(int j = 0, k = i % n; j < n; ++j, (++k) == n && (k = 0))
			buf[cur][j] = buf[pre][j] ^ buf[pre][k];
	}
	for(int i = 0; i < n; ++i)
		buf[cur][i] += 'A';
	puts(buf[cur]);
	return 0;
}
