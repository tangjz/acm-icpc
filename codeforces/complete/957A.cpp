#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
const char *pat = "CMY";
int n, f[3], g[3];
char buf[maxn];
int main() {
	scanf("%d%s", &n, buf);
	for(int i = 0; i < 3; ++i)
		if(buf[0] == '?' || buf[0] == pat[i])
			++f[i];
	for(int i = 1; i < n; ++i) {
		g[0] = g[1] = g[2] = 0;
		for(int j = 0; j < 3; ++j) {
			if(buf[i] != '?' && buf[i] != pat[j])
				continue;
			for(int k = 0; k < 3; ++k)
				if(j != k)
					g[j] += f[k];
			g[j] = min(g[j], 2);
		}
		swap(f, g);
	}
	puts(f[0] + f[1] + f[2] >= 2 ? "Yes" : "No");
	return 0;
}
