#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, a[maxn], p[maxn], sg[maxn], tim[maxn];
char buf[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		p[a[i]] = i;
	}
	for(int i = n; i >= 1; --i) {
		int x = p[i];
		for(int j = i; j <= n; j += i) {
			if(x - j >= 1 && a[x - j] > i)
				tim[sg[x - j]] = i;
			if(x + j <= n && a[x + j] > i)
				tim[sg[x + j]] = i;
		}
		for(sg[x] = 0; tim[sg[x]] == i; ++sg[x]);
		buf[x - 1] = sg[x] ? 'A' : 'B';
	}
	puts(buf);
	return 0;
}
