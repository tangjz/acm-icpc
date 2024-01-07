#include <cstring>

#include <iostream>

using namespace std;


typedef long long i64;

int T, a[19];
i64 f[19][2][2], g[19][2][2];

i64 calc(i64 x) {
	int m = 0;
	if (x == 0) return 0; // 0, 1
	while (x) {
		a[m++] = x % 10;
		x /= 10;
	}
	i64 sum = 0;
	for (int n = 1; n <= m; ++n) {
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		if (n == m) {
			//f[n][0][0] = 1;
			g[n][0][0] = 1;
		} else {
			//f[n][1][0] = 1;
			g[n][1][0] = 1;
		}
		for (int i = n - 1; i >= 0; --i) {
			for (int j = 0; j <= 9; ++j) {
				if (i == n - 1 && j == 0) continue;
				if (j < a[i]) {
					if (j & 1) {
						g[i][1][0] += g[i + 1][0][1];
						g[i][1][1] += g[i + 1][0][0];
						g[i][1][1] += f[i + 1][0][1];
					} else {
						f[i][1][0] += f[i + 1][0][1];
						f[i][1][1] += f[i + 1][0][0];
						f[i][1][1] += g[i + 1][0][0];
					}
				}
				if (j == a[i]) {
					if (j & 1) {
						g[i][0][0] += g[i + 1][0][1];
						g[i][0][1] += g[i + 1][0][0];
						g[i][0][1] += f[i + 1][0][1];
					} else {
						f[i][0][0] += f[i + 1][0][1];
						f[i][0][1] += f[i + 1][0][0];
						f[i][0][1] += g[i + 1][0][0];
					}
				}
				if (j & 1) {
					g[i][1][0] += g[i + 1][1][1];
					g[i][1][1] += g[i + 1][1][0];
					g[i][1][1] += f[i + 1][1][1];
				} else {
					f[i][1][0] += f[i + 1][1][1];
					f[i][1][1] += f[i + 1][1][0];
					f[i][1][1] += g[i + 1][1][0];
				}
			}
		}
		sum += f[0][0][1] + f[0][1][1] + g[0][0][0] + g[0][1][0];
		//cout << f[0][0][1] << ' ' << f[0][1][1] << ' ' << g[0][0][0] << ' ' << g[0][1][0] << endl;
		//cout << "sum: " << sum << endl;
	}
	return sum;
}

int main() {
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		i64 l, r;
		cin >> l >> r;
		//cout << "r: " << calc(r) << endl;
		cout << "Case #" << t << ": ";
		cout << calc(r) - calc(l - 1) << endl;
	}
	return 0;
}
