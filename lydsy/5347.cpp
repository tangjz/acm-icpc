#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e7 + 1;
int n, m, x, y, z, a[maxn];
int main() {
	scanf("%d%d%d%d%d", &n, &m, &x, &y, &z);
	for(int i = 0; i < n; ++i) {
		a[i] = i;
		m = ((LL)m * x + y) % z;
		swap(a[i], a[m % (i + 1)]);
	}
	m = 0;
	for(int i = 0; i < n; ++i)
		m = max(m, i - a[i]);
	printf("%d\n", m);
	return 0;
}
