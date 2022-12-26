#include <bits/stdc++.h>
using namespace std;
const int maxn = 301;
int n, m, f[maxn][maxn][maxn];
char buf[maxn];
int F(int L, int R, int c) {
	if(L >= R)
		return L == R;
	if(f[L][R][c] != -1)
		return f[L][R][c];
	int ret = max(F(L + 1, R, c), F(L, R - 1, c));
	if(buf[L] == buf[R])
		ret = max(ret, F(L + 1, R - 1, c) + 2);
	if(c)
		ret = max(ret, F(L + 1, R - 1, c - 1) + 2);
	return f[L][R][c] = ret;
}
int main() {
	scanf("%s%d", buf, &m);
	n = strlen(buf);
	memset(f, -1, sizeof f);
	printf("%d\n", F(0, n - 1, m));
	return 0;
}
