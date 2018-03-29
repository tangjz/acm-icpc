#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int n, x, y, p[maxn];
int main() {
	scanf("%d%d%d", &n, &x, &y);
	for(int a = 0; a * x <= n; ++a) {
		int adt = a * x;
		if((n - adt) % y > 0)
			continue;
		int b = (n - adt) / y;
		for(int i = 0; i < a; ++i) {
			p[x * i] = x * (i + 1) - 1;
			for(int j = 1; j < x; ++j)
				p[x * i + j] = x * i + (j - 1);
		}
		for(int i = 0; i < b; ++i) {
			p[adt + y * i] = adt + y * (i + 1) - 1;
			for(int j = 1; j < y; ++j)
				p[adt + y * i + j] = adt + y * i + (j - 1);
		}
		for(int i = 0; i < n; ++i)
			printf("%d%c", p[i] + 1, " \n"[i == n - 1]);
		return 0;
	}
	puts("-1");
	return 0;
}
