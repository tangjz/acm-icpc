#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define x first
#define y second
const int maxn = (int)1e4 + 1, mod = (int)1e9;
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
pair<int, int> solve(char pat[], int &pos) {
	char ch = pat[pos++];
	if(ch >= '1' && ch <= '9') {
		pair<int, int> dlt = make_pair(0, 0), tmp;
		assert(pat[pos++] == '(');
		while(pat[pos] != ')') {
			tmp = solve(pat, pos);
			mod_inc(dlt.x, tmp.x);
			mod_inc(dlt.y, tmp.y);
		}
		++pos;
		int mul = ch - '0';
		dlt.x = (LL)dlt.x * mul % mod;
		dlt.y = (LL)dlt.y * mul % mod;
		return dlt;
	} else {
		static const char *dir = "NSEW";
		static const pair<int, int> sft[4] = {
			{0, mod - 1}, {0, 1}, {1, 0}, {mod - 1, 0}
		};
		for(int i = 0; i < 4; ++i)
			if(ch == dir[i])
				return sft[i];
		assert(false);
	}
}
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		static char X[maxn + 3];
		scanf("%s", X + 2);
		int N = strlen(X + 2);
		X[0] = '1';
		X[1] = '(';
		X[N + 2] = ')';
		int pos = 0;
		pair<int, int> dlt = solve(X, pos);
		printf("Case #%d: %d %d\n", Case, dlt.x + 1, dlt.y + 1);
	}
	return 0;
}
