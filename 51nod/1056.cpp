#include <cmath>
#include <stdio.h>
#include <algorithm>
#include <unordered_map>
using namespace std;
namespace std {
	template<>
	struct hash<pair<int, int> > {
		size_t operator () (pair<int, int> const &t) const {
			return std::hash<long long>()((long long)t.first << 32 | t.second);
		}
	};
}
typedef unordered_map<pair<int, int>, int> AP;
const int maxn = 50001, maxl = 6001;
int n, a[maxn], bound[maxn], lim = 200;
unordered_map<int, int> idx;
short f[maxl][maxl];
AP solve(int L, int R, int dep)
{
	int n = R - L + 1, *b = a + L, &&len = lim >> dep;
	if(n < len)
		return AP();
	if(n < maxl && len <= bound[n])
	{
		for(int j = n - 1; j >= 0; --j)
		{
			int i = j - 1, k = j + 1;
			while(i >= 0 && k < n)
				if(b[i] + b[k] < (b[j] << 1))
					++k;
				else if(b[i] + b[k] > (b[j] << 1))
					f[i--][j] = 2;
				else
					f[i--][j] = f[j][k++] + 1;
			for( ; i >= 0; --i)
				f[i][j] = 2;
		}
		AP ret;
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
				if(f[i][j] >= len)
				{
					int prev = (b[i] << 1) - b[j];
					if(prev < b[0] || !idx.count(prev))
					{
						ret[make_pair(b[i], b[j] - b[i])] = f[i][j];
						if(lim <= f[i][j])
							lim = f[i][j] + 1;
					}
				}
		return ret;
	}
	int M = (L + R) >> 1;
	AP lch = solve(L, M, dep + 1), rch = solve(M + 1, R, dep + 1), ret, tmp;
	for(auto &it : lch)
	{
		int st = it.first.first, dt = it.first.second, sz = it.second, nxt = st + sz * dt;
		if(len - sz >= len >> 1)
		{
			pair<int, int> state = make_pair(nxt, dt);
			if(!rch.count(state))
				continue;
			int tp = rch[state];
			sz += tp;
			nxt += tp * dt;
		}
		for( ; nxt <= a[R] && idx.count(nxt); ++sz, nxt += dt);
		if(sz >= len)
		{
			ret[it.first] = sz;
			if(lim <= sz)
				lim = sz + 1;
		}
	}
	for(auto &it : rch)
	{
		int st = it.first.first, dt = it.first.second, sz = it.second, nxt = st - dt;
		if(len - sz >= len >> 1)
		{
			pair<int, int> state = make_pair(st - (len - sz) * dt, dt);
			if(!lch.count(state))
				continue;
			nxt -= (len - sz) * dt;
			sz = len;
		}
		for( ; nxt >= a[L] && idx.count(nxt); ++sz, nxt -= dt);
		st = nxt + dt;
		if(sz >= len)
		{
			pair<int, int> state = make_pair(st, dt);
			if(!ret.count(state) || ret[state] < sz)
			{
				ret[state] = sz;
				if(lim <= sz)
					lim = sz + 1;
			}
		}
	}
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
	{
		bound[i] = (int)floor(log2(i) + 1e-8);
		idx[a[i]] = i;
	}
	AP S = solve(1, n, 0);
	if(lim == 200)
		puts("No Solution");
	else
		printf("%d\n", lim - 1);
	return 0;
}
