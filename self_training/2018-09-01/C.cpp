#include <bits/stdc++.h>
using namespace std;
const int maxn = 201, maxm = (int)2e4 + 1, maxv = 13;
int t, n, m, a[maxm], b[maxn][maxv];
inline int getLow(int b[]) {
	for(int i = 0; i < maxv; ++i)
		if(b[i])
			return i;
	return -1;
}
inline int getNext(int b[], int v) {
	if(v == maxv - 1)
		return -1;
	if(b[v + 1])
		return v + 1;
	return b[maxv - 1] ? maxv - 1 : -1;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++i) {
			scanf("%d", a + i);
			(a[i] -= 3) < 0 && (a[i] += 13);
		}
		reverse(a, a + m);
		memset(b, 0, n * sizeof b[0]);
		for(int i = 0; i < n; ++i)
			for(int j = 0; m && j < 5; ++j)
				++b[i][a[--m]];
		int cur = 0, val = getLow(b[cur]);
		--b[cur][val];
		while(1) {
			bool chk = 1;
			for(int i = 1; i < n; ++i) {
				int tmp = getNext(b[(cur + i) % n], val);
				if(tmp != -1) {
					chk = 0;
					cur = (cur + i) % n;
					val = tmp;
					--b[cur][tmp];
					break;
				}
			}
			if(getLow(b[cur]) == -1)
				break;
			if(chk) {
				for(int i = 0; m > 0 && i < n; ++i)
					++b[(cur + i) % n][a[--m]];
				val = getLow(b[cur]);
				--b[cur][val];
				if(getLow(b[cur]) == -1)
					break;
			}
		}
		printf("Case #%d:\n", Case);
		for(int i = 0; i < n; ++i) {
			int sum = 0;
			for(int j = 0; j < maxv; ++j) {
				int k = j + 3 <= 13 ? j + 3 : j + 3 - 13;
				sum += k * b[i][j];
			}
			if(sum)
				printf("%d\n", sum);
			else
				puts("Winner");
		}
	}
	return 0;
}
