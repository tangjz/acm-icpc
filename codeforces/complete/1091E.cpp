#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1;
int n, a[maxn], b[maxn];
int check(int x) {
	for(int i = 0; i <= n; ++i)
		if(a[i] <= x) {
			memcpy(b, a, i * sizeof(int));
			b[i] = x;
			memcpy(b + i + 1, a + i, (n - i) * sizeof(int));
			x = i;
			break;
		}
	LL lft = 0, rht = 0;
	for(int i = 0, j = n; i <= n; ++i) {
		for( ; j > i && b[j] <= i; --j)
			rht += b[j];
		lft += b[i];
		LL chk = lft - rht - j * (i + 1LL);
		if(chk > 0)
			return x <= i ? 1 : -1;
		if(j == i)
			rht -= b[++j];
	}
	return 0;
}
int main() {
	scanf("%d", &n);
	bool odd = 0;
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		odd ^= a[i] & 1;
	}
	sort(a, a + n, greater<int>());
	int L = 0, R = n + 1;
	L += (L & 1) != odd;
	R += (R & 1) != odd;
	while(L < R) {
		int M = L + (R - L) / 4 * 2;
		if(check(M) < 0) {
			L = M + 2;
		} else {
			R = M;
		}
	}
	int low = L;
	L -= 2;
	R = n;
	R -= (R & 1) != odd;
	while(L < R) {
		int M = L + (R - L + 2) / 4 * 2;
		if(check(M) > 0) {
			R = M - 2;
		} else {
			L = M;
		}
	}
	int upp = L;
	if(0 <= low && low <= upp && upp <= n) {
		for( ; low <= upp; low += 2)
			printf("%d%c", low, " \n"[low == upp]);
	} else {
		puts("-1");
	}
	return 0;
}
