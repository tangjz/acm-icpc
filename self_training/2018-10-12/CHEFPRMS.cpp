#include <bits/stdc++.h>
using namespace std;
const int maxn = 201;
int t, n;
bool f[3][maxn];
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!f[0][i])
			for(int j = i + i; j < maxn; j += i)
				f[0][j] = 1;
		f[0][i] = !f[0][i];
	}
	for(int i = 1; i < maxn; ++i)
		if(f[0][i])
			for(int j = i, k = 1; j < maxn; j += i, ++k)
				f[1][j] |= i != k && f[0][k];
	for(int i = 1; i < maxn; ++i)
		if(f[1][i])
			for(int j = i, k = 0; j < maxn; ++j, ++k)
				f[2][j] |= f[1][k];
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		puts(f[2][n] ? "YES" : "NO");
	}
	return 0;
}
