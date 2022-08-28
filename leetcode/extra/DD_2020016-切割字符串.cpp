#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, kk, f[maxn];
char s[maxn];
int main() {
	scanf("%d%d%s", &n, &kk, s);
	for(int i = 1, j = 0; i < n; ++i) {
		for( ; j && s[i] != s[j]; j = f[j]);
		f[i + 1] = s[i] == s[j] ? (++j) : 0;
	}
	for(int i = 0; i < n; ++i) {
		int t = (i + 1) / (i + 1 - f[i + 1]);
        s[i] = "01"[t / kk + ((i + 1) % (i + 1 - f[i + 1]) == 0) > t % kk];
	}
    puts(s);
	return 0;
}
