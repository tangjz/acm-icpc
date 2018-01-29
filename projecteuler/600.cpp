#include <bits/stdc++.h>
using namespace std;
int main() {
	for(int n = 1; n <= 100; ++n) {
		int ways = 0;
		for(int a = 1; a <= n; ++a)
			for(int b = 1; a + b <= n; ++b)
				for(int c = 1; a + b + c <= n; ++c)
					for(int d = 1; a + b + c + d <= n; ++d) {
						int e = a + b - d, f = b + c - e;
						if(c + d - f == a && e >= 1 && f >= 1 && a + b + c + d + e + f == n) {
							int pat[7] = {a, b, c, d, e, f};
							string cur = "";
							for(int i = 0; i < 6; ++i)
								cur += pat[i];
							bool chk = 1;
							for(int i = 1; chk && i < 6; ++i) {
								string tmp = "";
								for(int j = 0; j < 6; ++j)
									tmp += pat[(i + j) % 6];
								chk &= cur <= tmp;
							}
							for(int i = 0; chk && i < 6; ++i) {
								string tmp = "";
								for(int j = 5; j >= 0; --j)
									tmp += pat[(i + j) % 6];
								chk &= cur <= tmp;
							}
							if(chk) {
								++ways;
								// printf("%d %d %d %d %d %d\n", a, b, c, d, e, f);
							}
						}
					}
		printf("%d: %d\n", n, ways);
	}
	const int maxn = 55107;
	static long long f[maxn];
	f[6] = 1;
	for(int i = 1; i < maxn; ++i)
		f[i] += f[i - 1];
	for(int i = 2; i < maxn; ++i)
		f[i] += f[i - 2];
	for(int i = 3; i < maxn; ++i)
		f[i] += f[i - 3];
	for(int i = 4; i < maxn; ++i)
		f[i] += f[i - 4];
	for(int i = 6; i < maxn; ++i)
		f[i] += f[i - 6];
	printf("%lld\n", f[6]);
	printf("%lld\n", f[12]);
	printf("%lld\n", f[100]);
	printf("%lld\n", f[maxn - 1]);
	return 0;
}
