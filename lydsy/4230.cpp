#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxl = 19, maxd = 10, maxs = 1 << 9;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
struct Info {
	LL step;
	void operator += (Info const &t) {
		if(step > t.step)
			step = t.step;
	}
	Info operator * (Info const &t) const { // assume step + t.step < INF
		return (Info){step + t.step};
	}
} ;
struct Matrix {
	Info mat[maxd | 1][maxd | 1];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		for(int i = 0; i < maxd; ++i)
			for(int j = 0; j < maxd; ++j)
				ret.mat[i][j] = (Info){INF};
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
			for(int j = 0; j < maxd + i; ++j)
				dp[j] = (Info){INF};
			dp[maxd + i] = (Info){0};
			for(int j = i; j >= 0; --j) {
				if(dp[maxd + j].step == INF)
					continue;
				for(int k = 1; k < maxd; ++k)
					if((mask | msk[j]) & msk[k])
						dp[maxd + j - k] += (Info){dp[maxd + j].step + 1};
			}
			for(int j = 0; j < maxd; ++j)
				f[len][mask].mat[i][j] = dp[j];
		}
	} else {
		f[len][mask] = F(len - 1, mask | msk[maxd - 1]);
		for(int i = maxd - 2; i >= 0; --i)
			f[len][mask] = f[len][mask] * F(len - 1, mask | msk[i]);
	}
	return f[len][mask];
}
Info solve(LL n) {
	static char buf[(maxl + 1) | 1];
	int len = sprintf(buf, "%lld", n);
	reverse(buf, buf + len);
	static Info vec[maxd | 1], tmp[maxd | 1];
	for(int i = 0; i < maxd; ++i)
		vec[i] = (Info){INF};
	vec[buf[0] - '0'] = (Info){0};
	for(int i = 1; i < len; ++i) {
		int mask = 0;
		for(int j = i + 1; j < len; ++j)
			mask |= msk[buf[j] - '0'];
		int sta = buf[i] - '0' - (i > 1), end = -(i + 1 < len);
		for(int j = sta; j > end; --j) {
			Matrix &cur = F(i, mask | msk[j]);
			for(int x = 0; x < maxd; ++x)
				tmp[x] = (Info){INF};
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
	}
	for(int i = len - 2; i >= 1; --i)
		for(int j = maxd - 1; j > 0; --j) {
			Matrix &cur = F(i, msk[j]);
			for(int x = 0; x < maxd; ++x)
				tmp[x] = (Info){INF};
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
	for(int i = maxd - 1; i > 0; --i) {
		if(vec[i].step == INF)
			continue;
		vec[0] += (Info){vec[i].step + 1};
	}
	return vec[0];
}
int main() {
	for(int i = 1; i < maxd; ++i)
		msk[i] = 1 << (i - 1);
	LL n;
	scanf("%lld", &n);
	printf("%lld\n", solve(n).step);
	return 0;
}
