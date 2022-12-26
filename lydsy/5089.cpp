#include <cstdio>
typedef long long LL;
const int maxn = 50001;
int n, m;
LL a[maxn];
int main() {
	scanf("%d%d ", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%lld ", a + i);
	while(m--) {
		char op;
		int L, R;
		scanf("%c%d%d ", &op, &L, &R);
		if(op == 'A') {
			int x;
			scanf("%d ", &x);
			while(L <= R)
				a[L++] += x;
		} else {
			LL x = 0, y = 0;
			while(L <= R)
				(x += a[L++]) < 0 ? (x = 0) : (y < x && (y = x));
			printf("%lld\n", y);
		}
	}
	return 0;
}
