#include <stdio.h>
typedef long long LL;
const int maxn = 101;
int n, m, pos, cnt, a[maxn], s1, s2, bit[maxn];
void bit_add(int x, int v) {
	for( ; x < maxn; x += ~x & (x + 1))
		bit[x] += v;
}
int bit_que(int k) {
	int x = 0;
	for(int y = 1 << 6, z; y; y >>= 1)
		if((z = x | y) <= maxn && bit[z - 1] < k) {
			x = z;
			k -= bit[z - 1];
		}
	return x;
}
int main() {
	scanf("%d%d", &m, &n);
	for(int i = 0; i < n; ++i)
		a[i] = -1;
	while(m--) {
		int typ, x;
		scanf("%d", &typ);
		if(typ == 1) {
			scanf("%d", &x);
			if(a[pos] == -1) {
				++cnt;
			} else {
				s1 -= a[pos];
				s2 -= a[pos] * a[pos];
				bit_add(a[pos], -1);
			}
			a[pos++] = x;
			s1 += x;
			s2 += x * x;
			bit_add(x, 1);
			if(pos == n)
				pos = 0;
		} else if(typ == 2) {
			printf("%.2f\n", (double)(s1 / cnt));
		} else if(typ == 3) {
			printf("%.2f\n", s2 / (double)cnt - (LL)s1 * s1 / (double)(cnt * cnt));
		} else {
			int p1 = (cnt + 1) >> 1, p2 = cnt + 1 - p1;
			printf("%.2f\n", p1 == p2 ? bit_que(p1) : (bit_que(p1) + bit_que(p2)) * 0.5);
		}
	}
	return 0;
}
