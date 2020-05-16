#include <bits/stdc++.h>
using namespace std;
const int maxn = 2001;
int n, m, out[maxn * 3];
char s[maxn], t[maxn];
void shift(int x) {
	reverse(s, s + n);
	if(x < n)
		reverse(s + x, s + n);
	out[m++] = x;
}
int main() {
	scanf("%d%s%s", &n, s, t);
	for(int i = n - 1, j; i >= 0; --i) {
		for(j = n - 1 - i; j < n && s[j] != t[i]; ++j);
		if(j == n) {
			puts("-1");
			return 0;
		}
		shift(n);
		shift(j);
		shift(1);
	}
	printf("%d\n", m);
	for(int i = 0; i < m; ++i)
		printf("%d%c", out[i], " \n"[i == m - 1]);
	return 0;
}
