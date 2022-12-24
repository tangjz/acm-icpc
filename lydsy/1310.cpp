#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 61;
int n, m, len, cnt;
LL rk, c[maxn][maxn];
char buf[maxn];
inline LL calc() {
	LL ret = 0;
	if(len + len > n) {
		int cnt = 0;
		static char s[maxn], t[maxn];
		for(int i = 0; i < n; ++i) {
			s[i] = i < len ? buf[i] : buf[n - 1 - i];
			cnt += i && s[i - 1] != s[i];
		}
		s[n] = '\0';
		strcpy(t, s);
		std::reverse(t, t + n);
		ret += cnt <= m && strcmp(s, t) <= 0;
	} else {
		LL adt = 0;
		for(int i = 0; i <= m - cnt - cnt; i += 2)
			adt += c[n + 1 - len - len][i] + c[(n + 1) / 2 - len][i / 2];
		assert(!(adt & 1));
		ret += adt >> 1;
	}
	for(int i = 0, cnt2 = cnt; i < len && i + len < n; ++i) {
		if(buf[i] == 'I') {
			cnt2 += i && buf[i - 1] != 'X';
			for(int j = 1; j + cnt2 <= m; j += 2)
				ret += c[n - len - i][j];
			cnt2 -= i && buf[i - 1] != 'X';
		}
		cnt2 += i && buf[i - 1] != buf[i];
	}
	return ret;
}
int main() {
	for(int i = 0; i < maxn; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	scanf("%d%d%lld", &n, &m, &rk);
	for(int i = 0; i < n; ++i) {
		buf[len++] = 'I';
		cnt += len > 1 && buf[len - 2] != buf[len - 1];
		LL ways = calc();
		if(rk > ways) {
			rk -= ways;
			cnt -= len > 1 && buf[len - 2] != buf[len - 1];
			buf[len - 1] = 'X';
			cnt += len > 1 && buf[len - 2] != buf[len - 1];
		}
	}
	buf[len] = '\0';
	puts(rk > 1 ? "NO SUCH STONE" : buf);
	return 0;
}
