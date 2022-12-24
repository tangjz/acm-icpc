#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, mod[2] = {(int)1e9 + 7, (int)1e9 + 9};
int pw[2][maxn], len[2], f[2][maxn], g[2][maxn];
pair<LL, int> seq[2][maxn];
char buf[maxn];
void init(int len, pair<LL, int> res[]) {
	for(int i = 1, o; i <= len; ++i) {
		o = buf[i - 1] - ' ';
		f[0][i] = (97LL * f[0][i - 1] + o) % mod[0];
		f[1][i] = (97LL * f[1][i - 1] + o) % mod[1];
		o = buf[len - i] - ' ';
		g[0][i] = (97LL * g[0][i - 1] + o) % mod[0];
		g[1][i] = (97LL * g[1][i - 1] + o) % mod[1];
	}
	for(int i = 1; i <= len; ++i) {
		int h0 = ((f[0][len] - (LL)f[0][i] * pw[0][len - i] - g[0][len - i]) % mod[0] * pw[0][i] + g[0][len]) % mod[0];
		h0 < 0 && (h0 += mod[0]);
		int h1 = ((f[1][len] - (LL)f[1][i] * pw[1][len - i] - g[1][len - i]) % mod[1] * pw[1][i] + g[1][len]) % mod[1];
		h1 < 0 && (h1 += mod[1]);
		res[i - 1] = make_pair((LL)h0 << 32 | h1, i - 1);
	}
}
int main() {
	pw[0][0] = pw[1][0] = 1;
	for(int i = 1; i < maxn; ++i) {
		pw[0][i] = 97LL * pw[0][i - 1] % mod[0];
		pw[1][i] = 97LL * pw[1][i - 1] % mod[1];
	}
	gets(buf);
	len[0] = strlen(buf);
	init(len[0], seq[0]);
	sort(seq[0], seq[0] + len[0]);
	gets(buf);
	len[1] = strlen(buf);
	reverse(buf, buf + len[1]);
	init(len[1], seq[1]);
	sort(seq[1], seq[1] + len[1]);
	pair<int, int> ans = make_pair(maxn, maxn);
	if(len[0] == len[1])
		for(int i = 0, j = 0; i < len[1]; ++i) {
			for( ; j < len[0] && seq[0][j] < seq[1][i]; ++j);
			if(j < len[0] && seq[0][j].first == seq[1][i].first && seq[0][j].second + 1 < len[0])
				ans = min(ans, make_pair(-seq[1][i].second, seq[0][j].second + 1));
		}
	if(ans.first < maxn)
		printf("%d %d\n", -ans.first, ans.second);
	else
		puts("-1 -1");
	return 0;
}
