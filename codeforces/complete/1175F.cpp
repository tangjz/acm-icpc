#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)3e5 + 1;
int n, a[maxn], st, tim[maxn], val[maxn], ans;
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i) {
		if(a[i] != 1)
			continue;
		val[i] = 1;
		for(int j = i - 1; j >= 1 && a[j] != 1; --j)
			val[j] = max(val[j + 1], a[j]);
		for(int j = i + 1; j <= n && a[j] != 1; ++j)
			val[j] = max(val[j - 1], a[j]);
		{ // max at left
			int L = i, R = i;
			++st;
			for( ; L >= 1 && tim[a[L]] != st; --L)
				tim[a[L]] = st;
			for(++L; L <= i; tim[a[L++]] = st - 1) {
				for( ; i < R && (R - L + 1 > val[L] || val[R] >= val[L]); tim[a[R--]] = st - 1);
				for( ; R < n && R - L + 1 < val[L]; tim[a[++R]] = st)
					if(a[R + 1] >= val[L] || tim[a[R + 1]] == st)
						break;
				if(R - L + 1 == val[L])
					++ans;
			}
		}
		{ // max at right
			int L = i, R = i;
			++st;
			for( ; R <= n && tim[a[R]] != st; ++R)
				tim[a[R]] = st;
			for(--R; i <= R; tim[a[R--]] = st - 1) {
				for( ; L < i && (R - L + 1 > val[R] || val[L] >= val[R]); tim[a[L++]] = st - 1);
				for( ; L > 1 && R - L + 1 < val[R]; tim[a[--L]] = st)
					if(a[L - 1] >= val[R] || tim[a[L - 1]] == st)
						break;
				if(R - L + 1 == val[R])
					++ans;
			}
		}
		--ans;
	}
	printf("%d\n", ans);
	return 0;
}