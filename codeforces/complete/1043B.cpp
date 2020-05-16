#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1;
int n, a[maxn], m, seq[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int i = n - 1; i > 0; --i)
		a[i] -= a[i - 1];
	for(int i = 1; i <= n; ++i) {
		bool chk = 1;
		for(int j = i; j < n && chk; ++j)
			chk &= a[j] == a[j - i];
		if(chk) {
			seq[m++] = i;
		}
	}
	printf("%d\n", m);
	for(int i = 0; i < m; ++i)
		printf("%d%c", seq[i], " \n"[i == m - 1]);
	return 0;
}