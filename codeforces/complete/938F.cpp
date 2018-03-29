#include <bits/stdc++.h>
using namespace std;
const int maxn = 5001;
int n, m;
char buf[maxn], out[maxn];
bool f[maxn];
int main() {
	scanf("%s", buf);
	n = strlen(buf);
	for(m = 0; 2 << m <= n; ++m);
	for(int i = 0; i < 1 << m; ++i)
		f[i] = 1;
	for(int i = 0; i <= n - (1 << m); ++i) {
		out[i] = 'z';
		for(int j = 0; j < 1 << m; ++j)
			if(f[j])
				out[i] = min(out[i], buf[i + j]);
		for(int j = 0; j < 1 << m; ++j)
			f[j] = f[j] && out[i] == buf[i + j];
		for(int j = 1; j < 1 << m; j <<= 1)
			for(int k = 0; k < 1 << m; ++k)
				if(k & j)
					f[k] |= f[k ^ j];
	}
	out[n - (1 << m) + 1] = '\0';
	puts(out);
	return 0;
}
