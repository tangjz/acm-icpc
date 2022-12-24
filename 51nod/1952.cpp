#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 10000001, mod = (int)1e9 + 7;
int n, A, B, C, x, a, b, p, top, stk[maxn], L, R, sL, sR, ans;
std::pair<int, int> que[maxn];
int main() {
	scanf("%d%d%d%d%d%d%d%d", &n, &A, &B, &C, &x, &a, &b, &p);
	while(n--) {
		x = ((LL)a * x + b) % p;
		int y = x % (A + B + C);
		if(top + R - L <= 1 || y < A) {
			stk[top] = std::max(x, stk[top - 1]);
			++top;
		} else if(y < A + B) {
			for( ; sL < sR && que[sR - 1].first < x; --sR);
			que[sR++] = std::make_pair(x, R++);
		} else {
			if(top) {
				--top;
			} else {
				sL += que[sL].second == L;
				++L;
			}
		}
		if(L == R || (top && stk[top - 1] > que[sL].first))
			(ans += stk[top - 1]) >= mod && (ans -= mod);
		else
			(ans += que[sL].first) >= mod && (ans -= mod);
	}
	printf("%d\n", ans);
	return 0;
}
