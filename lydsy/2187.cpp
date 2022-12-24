#include <bits/stdc++.h>
using namespace std;
inline int solve(int a, int b, int c, int d) {
	int p = a / b;
	a -= p * b;
	c -= p * d;
	if(c > d)
		return 1;
	if(!a)
		return d / c + 1;
	return p = (long long)solve(d, c, b, a) * d / c + 1;
}
int main() {
	int a, b, c, d;
	while(scanf("%d%d%d%d", &a, &b, &c, &d) == 4) {
		int q = solve(a, b, c, d);
		int p = (long long)q * a / b + 1;
		printf("%d/%d\n", p, q);
	}
	return 0;
}