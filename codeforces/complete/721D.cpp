#include <cmath>
#include <queue>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 200001;
const double eps = 1e-9;
int sgn(double x)
{
	return (x > eps) - (x < -eps);
}
int n, m, v, a[maxn];
void solve_abs_max()
{
	static LL b[maxn];
	std::priority_queue<std::pair<double, int> > Q;
	for(int i = 0; i < n; ++i)
	{
		b[i] = a[i];
		LL tp = std::abs(b[i]);
		Q.push(std::make_pair(log(tp + v) - log(tp), i));
	}
	while(m--)
	{
		double dt = Q.top().first;
		if(sgn(dt) < 0)
			break;
		int i = Q.top().second;
		Q.pop();
		if(b[i] > 0)
			b[i] += v;
		else
			b[i] -= v;
		LL tp = std::abs(b[i]);
		Q.push(std::make_pair(log(tp + v) - log(tp), i));
	}
	for(int i = 0; i < n; ++i)
		printf("%I64d%c", b[i], " \n"[i == n - 1]);
}
void solve_abs_min()
{
	static LL b[maxn];
	std::priority_queue<std::pair<double, int> > Q;
	for(int i = 0; i < n; ++i)
	{
		b[i] = a[i];
		LL tp = std::abs(b[i]);
		Q.push(std::make_pair(log(tp) - log(tp - v), i));
	}
	while(m--)
	{
		double dt = Q.top().first;
		if(sgn(dt) < 0)
			break;
		int i = Q.top().second;
		Q.pop();
		if(b[i] > 0)
			b[i] -= v;
		else
			b[i] += v;
		LL tp = std::abs(b[i]);
		Q.push(std::make_pair(log(tp) - log(tp - v), i));
	}
	for(int i = 0; i < n; ++i)
		printf("%I64d%c", b[i], " \n"[i == n - 1]);
}
int main()
{
	scanf("%d%d%d", &n, &m, &v);
	int neg_cnt = 0, zero_cnt = 0, mod_cnt = 0;
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		neg_cnt += a[i] < 0;
		zero_cnt += !a[i];
		mod_cnt += !(a[i] % v);
	}
	// try to be negative
	if(m >= zero_cnt) // 0 -> x or -x
	{
		bool flag = 0;
		if(zero_cnt)
		{
			flag = 1;
			for(int i = 0; i < n; ++i)
			{
				if(a[i])
					continue;
				if(neg_cnt & 1)
					a[i] = v;
				else
				{
					a[i] = -v;
					++neg_cnt;
				}
				--m;
			}
		}
		else if(neg_cnt & 1)
			flag = 1;
		else // zero_cnt = 0
		{
			int pos = -1;
			for(int i = 0; i < n; ++i)
			{
				if(!a[i])
					continue;
				if(pos == -1 || std::abs(a[pos]) > std::abs(a[i]))
					pos = i;
			}
			int need = std::abs(a[pos]) / v + 1;
			if(need <= m)
			{
				flag = 1;
				if(a[pos] < 0)
					a[pos] += v * need;
				else
					a[pos] -= v * need;
				m -= need;
			}
		}
		if(flag)
		{
			solve_abs_max();
			return 0;
		}
	}
	// try to be zero
	if(mod_cnt)
	{
		int pos = -1;
		for(int i = 0; i < n; ++i)
		{
			if(a[i] % v)
				continue;
			if(pos == -1 || std::abs(a[pos]) > std::abs(a[i]))
				pos = i;
		}
		int need = std::abs(a[pos]) / v;
		if(need <= m)
		{
			a[pos] = 0;
			for(int i = 0; i < n; ++i)
				printf("%d%c", a[i], " \n"[i == n - 1]);
			return 0;
		}
	}
	// try to be positive
	// zero_cnt = 0, each number could not change sign/unsign
	solve_abs_min();
	return 0;
}
