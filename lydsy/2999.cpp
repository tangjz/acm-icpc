#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxl = 10, maxd = 10, maxs = 1 << 9, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
struct Info {
	int step, ways;
	void operator += (Info const &t) {
		if(step > t.step) {
			step = t.step;
			ways = 0;
		}
		if(step == t.step)
			(ways += t.ways) >= mod && (ways -= mod);
	}
	Info operator * (Info const &t) const { // assume step + t.step < INF
		return (Info){step + t.step, (int)((LL)ways * t.ways % mod)};
	}
} ;
struct Matrix {
	Info mat[maxd | 1][maxd | 1];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		for(int i = 0; i < maxd; ++i)
			for(int j = 0; j < maxd; ++j)
				ret.mat[i][j] = (Info){INF, 0};
		for(int i = 0; i < maxd; ++i)
			for(int j = 0; j < maxd; ++j) {
				if(mat[i][j].step == INF)
					continue;
				for(int k = 0; k < maxd; ++k)
					if(t.mat[j][k].step < INF)
						ret.mat[i][k] += mat[i][j] * t.mat[j][k];
			}
		return ret;
	}
} f[maxl | 1][maxs | 1];
int msk[maxd | 1];
bool vis[maxl | 1][maxs | 1];
Matrix &F(int len, int mask) {
	if(vis[len][mask])
		return f[len][mask];
	vis[len][mask] = 1;
	if(len == 1) {
		for(int i = 0; i < maxd; ++i) {
			static Info dp[(maxd + maxd) | 1];
			for(int j = 0; j < maxd + maxd; ++j)
				dp[j] = (Info){INF, 0};
			dp[i] = (Info){0, 1};
			for(int j = i; j < maxd; ++j) {
				if(dp[j].step == INF)
					continue;
				for(int k = 1; k < maxd; ++k)
					if((mask | msk[j]) & msk[k])
						dp[j + k] += (Info){dp[j].step + 1, dp[j].ways};
			}
			for(int j = 0; j < maxd; ++j)
				f[len][mask].mat[i][j] = dp[maxd + j];
		}
	} else {
		f[len][mask] = F(len - 1, mask | msk[0]);
		for(int i = 1; i < maxd; ++i)
			f[len][mask] = f[len][mask] * F(len - 1, mask | msk[i]);
	}
	return f[len][mask];
}
Info solve(int n) {
	static char buf[(maxl + 1) | 1];
	int len = sprintf(buf, "%d", n);
	reverse(buf, buf + len);
	static Info vec[maxd | 1], tmp[maxd | 1];
	for(int i = 0; i < maxd; ++i)
		vec[i] = (Info){INF, 0};
	vec[1] = (Info){0, 1};
	int mask = 0;
	for(int i = len - 1; i >= 1; --i) {
		int dig = buf[i] - '0';
		for(int j = 0; j < dig; ++j) {
			Matrix &cur = F(i, mask | msk[j]);
			for(int x = 0; x < maxd; ++x)
				tmp[x] = (Info){INF, 0};
			for(int x = 0; x < maxd; ++x) {
				if(vec[x].step == INF)
					continue;
				for(int y = 0; y < maxd; ++y)
					if(cur.mat[x][y].step < INF)
						tmp[y] += vec[x] * cur.mat[x][y];
			}
			for(int x = 0; x < maxd; ++x)
				vec[x] = tmp[x];
		}
		mask |= msk[dig];
	}
	int dig = buf[0] - '0';
	for(int i = 0; i < dig; ++i) {
		if(vec[i].step == INF)
			continue;
		for(int j = 1; i + j <= dig; ++j)
			if((mask | msk[i]) & msk[j])
				vec[i + j] += (Info){vec[i].step + 1, vec[i].ways};
	}
	return vec[dig];
}
int main() {
	for(int i = 1; i < maxd; ++i)
		msk[i] = 1 << (i - 1);
	int n;
	while(scanf("%d", &n) == 1) {
		Info ret = solve(n);
		if(ret.step < INF)
			printf("%d %d\n", ret.step, ret.ways);
		else
			puts("IMPOSSIBLE");
	}
	return 0;
}
