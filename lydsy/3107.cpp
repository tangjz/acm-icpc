#include <bits/stdc++.h>
int main() {
	int a, b, c, mx = 0, x = 0, y = 0, z = 0;
	scanf("%d%d%d", &a, &b, &c);
	for( ; a || b || c; x += a & 1, a >>= 1, y += b & 1, b >>= 1, z += c & 1, c >>= 1, ++mx);
	int upp1 = std::max(x, y), upp2 = x + y - z, upp = std::max(upp1, upp2);
	printf("%d\n", x + y == z ? (1 << z) - 1 :
		!x || !y || std::max(upp, z) >= mx ? -1 :
		z < upp1 ? (1 << upp) ^ ((1 << z) - 1) ^ (1 << (upp - upp2)) :
			((1 << (z + 1)) - 1) ^ (1 << (z + z - x - y)));
	return 0;
}