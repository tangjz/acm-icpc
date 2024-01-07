#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxm = 6, maxd = 1 << 5 | 1, maxs = (int)1e3 + 1;
int dfs(int n, int tot, int upp, int sta, vector<int> &msk) {
	if((int)msk.size() == tot) {
		bool chk = 1;
		vector<int> perm(n);
		iota(perm.begin(), perm.end(), 0);
		static int tim = 0, vis[maxd] = {};
		++tim;
		for(int x : msk)
			vis[x] = tim;
		while(chk && next_permutation(perm.begin(), perm.end())) {
			bool same = 1;
			for(int x : msk) {
				int y = 0;
				for(int i = 0; i < n; ++i, x >>= 1)
					if(x & 1)
						y |= 1 << perm[i];
				if(vis[y] != tim) {
					same = 0;
					break;
				}
			}
			chk &= !same;
		}
		if(chk) {
			// for(int x : best) {
			// 	for(int j = 0; j < n; ++j, x >>= 1)
			// 		printf("%d", x & 1);
			// 	puts("");
			// }
			// puts("");
		}
		return chk;
	}
	int ret = 0;
	msk.push_back(0);
	for( ; sta < (1 << n) && ret < upp; ++sta) {
		msk.back() = sta;
		ret += dfs(n, tot, upp, sta + 1, msk);
	}
	msk.pop_back();
	return ret < upp ? ret : upp;
}
int solve1(LL n, int m) {
	if(n < m)
		return solve1(m, n);
	if(n > (1LL << m) - n)
		return solve1((1LL << m) - n, m);
	if(m > 5)
		return maxs;
	int prd = 1;
	for(int i = 1; i <= m; ++i)
		prd *= i;
	int upp = (maxs - 1) * prd + 1;
	vector<int> msk;
	int ret = dfs(m, n, upp, 0, msk);
	return ret < upp ? ret / prd : maxs;
}
set<vector<int> > Hash;
int dfs2(int n, int tot, int sta, vector<int> &msk, bool sp) {
	if((int)msk.size() == tot) {
		if(!sp)
			return 0;
		bool chk = 1;
		vector<int> perm(n), best = msk;
		iota(perm.begin(), perm.end(), 0);
		while(chk && next_permutation(perm.begin(), perm.end())) {
			vector<int> tmp;
			for(int x : msk) {
				int y = 0;
				for(int i = 0; i < n; ++i, x >>= 1)
					if(x & 1)
						y |= 1 << perm[i];
				tmp.push_back(y);
			}
			sort(tmp.begin(), tmp.end());
			chk &= msk != tmp;
			best = min(best, tmp);
		}
		chk &= !Hash.count(best);
		if(chk) {
			Hash.insert(best);
			// for(int x : best) {
			// 	for(int j = 0; j < n; ++j, x >>= 1)
			// 		printf("%d", x & 1);
			// 	puts("");
			// }
			// puts("");
		}
		return chk;
	}
	int ret = 0;
	msk.push_back(0);
	for( ; sta < (1 << n) && ret < maxs; ++sta) {
		msk.back() = sta;
		ret += dfs2(n, tot, sta, msk, sp || ((int)msk.size() > 2 && msk[msk.size() - 2] == sta));
	}
	msk.pop_back();
	return ret < maxs ? ret : maxs;
}
int solve2(int n, int m) {
	// printf("dangerous (%d, %d)\n", n, m);
	if(n == 4) {
		/*
			1100
			1100
			1010
		*/
		return 1;
	}
	if(n == 7) {
		/*
			1110000
			1110000
			1001100
			1101010

			1110000
			1101100
			1101100
			1011010
		*/
		return 2;
	}
	if(n == 8) {
		return 0;
	}
	// unreachable
	Hash.clear();
	vector<int> msk;
	return dfs2(n, m, 0, msk, 0);
}
int main() {
	LL n;
	int m = 0;
	scanf("%lld", &n);
	vector<int> dp = {0};
	for(int i = 1; i < n; ++i) {
		for(int j = 0; j < i; ++j)
			if((1 << j) - i >= dp[j]) {
				dp.push_back(j);
				break;
			}
		// assert((int)dp.size() == i + 1);
		if((1LL << i) - n >= dp.back()) {
			m = i;
			break;
		}
	}
	int ans = solve1(n, m);
	if(ans < maxs && n * 2 <= (1LL << m))
		ans += solve2(n, m);
	printf("%d\n", ans < maxs ? ans : -1);
	return 0;
}