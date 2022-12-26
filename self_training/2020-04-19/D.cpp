#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = (int)2e5 + 1;
int main() {
	static DB lgF[maxn];
	lgF[0] = lgF[1] = 0;
	for(int i = 2; i < maxn; ++i)
		lgF[i] = lgF[i - 1] + log(i);
	function<DB(int, int)> lgC = [&](int n, int m) {
		return m >= 0 && m <= n ? lgF[n] - lgF[m] - lgF[n - m] : -1;
	};
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int W, H, L, U, R, D;
		scanf("%d%d%d%d%d%d", &W, &H, &L, &U, &R, &D);
		--W;
		--H;
		--L;
		--U;
		--R;
		--D;
		map<pair<int, int>, DB> prob;
		prob[make_pair(0, 0)] = 1;
		function<DB(int, int)> getProb = [&](int X, int Y) {
			map<pair<int, int>, DB>::const_iterator it = prob.find(make_pair(X, Y));
			if(it != prob.end())
				return it -> second;
			if(X > 0 && X < W && Y > 0 && Y < H)
				return exp(lgC(X + Y, X) - lgF[2] * (X + Y));
			DB ret = 0;
			if(X > 0)
				ret += getProb(X - 1, Y) * (Y == H ? 1 : 0.5);
			if(Y > 0)
				ret += getProb(X, Y - 1) * (X == W ? 1 : 0.5);
			return prob[make_pair(X, Y)] = ret;
		};
		double ans = 1.0;
		// top-left: (L, U)
		{
			double tmp = getProb(L, U);
			ans -= tmp;
		}
		// top: (X, U)
		if(U > 0)
			for(int i = L + 1; i <= R; ++i) {
				double tmp = getProb(i, U - 1) * (i == W ? 1 : 0.5);
				ans -= tmp;
			}
		// left: (L, Y)
		if(L > 0)
			for(int i = U + 1; i <= D; ++i) {
				double tmp = getProb(L - 1, i) * (i == H ? 1 : 0.5);
				ans -= tmp;
			}
		printf("Case #%d: %.10f\n", Case, ans);
	}
	return 0;
}