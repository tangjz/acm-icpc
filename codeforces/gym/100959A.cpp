#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxp = 101, maxe = 61, maxw = 15, maxs = 32751;
const LL maxv = (LL)1e18;
int tot, pr[maxp], d[maxp], ctr, sz, ord[maxs], osz;
std::pair<LL, LL> fir[maxs], val[maxs];
LL plim[maxp], out[maxs];
bool vis[maxp];
struct Exp {
	int sig, len, ex[maxw]; // non-inc
} seq[maxs], pat;
bool cmp(int const &x, int const &y)
{
	Exp &a = seq[x], &b = seq[y];
	if(a.sig != b.sig)
		return a.sig < b.sig;
	if(a.len != b.len)
		return a.len < b.len;
	for(int i = 0; i < a.len; ++i)
		if(a.ex[i] != b.ex[i])
			return a.ex[i] < b.ex[i];
	return 0;
}
void pfs(int dep, LL val, int last)
{
	LL nxt = maxv + 1;
	for(int i = 0, j; i < pat.len; ++i)
		if(pat.ex[i] > pat.ex[i + 1])
		{
			LL tmp = val;
			for(j = pat.ex[i + 1]; j < pat.ex[i] && (tmp /= pr[i]) <= plim[i + 1]; ++j, tmp *= pr[i + 1]);
			if(j == pat.ex[i] && tmp < nxt)
				nxt = tmp;
		}
	ord[ctr] = ctr;
	fir[ctr] = std::make_pair(val, nxt);
	seq[ctr++] = pat;
	for(int i = 1; i <= last && val <= maxv / pr[dep]; ++i)
	{
		pat.sig *= i + 1;
		pat.ex[pat.len++] = i;
		pfs(dep + 1, val *= pr[dep], i);
		pat.sig /= i + 1;
		pat.ex[--pat.len] = 0;
	}
}
bool dfs(int dep, LL val, int last)
{
	if(dep == pat.len)
	{
		out[osz++] = val;
		return 1;
	}
	for(int i = last, j; i < tot; ++i)
	{
		if(vis[i])
			continue;
		LL nxt = val;
		for(j = pat.ex[dep]; j && nxt <= plim[i]; --j, nxt *= pr[i]);
		if(j)
			return last < i;
		vis[i] = 1;
		if(!dfs(dep + 1, nxt, pat.ex[dep] == pat.ex[dep + 1] ? i + 1 : 0))
		{
			vis[i] = 0;
			return last < i;
		}
		vis[i] = 0;
	}
	return last < tot;
}
int main()
{
	for(int i = 2; i < maxp; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxp; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pat = (Exp){1, 0};
	for(int i = 0; i < tot; ++i)
		plim[i] = maxv / pr[i];
	pfs(0, 1, maxe);
	std::sort(ord, ord + ctr, cmp);
	for(int i = 0; i < ctr; ++sz)
	{
		val[sz] = fir[ord[i]];
		LL &px = val[sz].first, &py = val[sz].second;
		for(LL sigma = seq[ord[i++]].sig; i < ctr && seq[ord[i]].sig == sigma; ++i)
		{
			LL cx = fir[ord[i]].first, cy = fir[ord[i]].second;
			if(cx < px && cy < px)
			{
				px = cx;
				py = cy;
			}
			else if(cx < px)
			{
				py = px;
				px = cx;
			}
			else if(cx < py)
				py = cx;
		}
	}
	LL limit = maxv;
	val[sz] = std::make_pair(maxv + 1, maxv + 1);
	LL &px = val[sz].first, &py = val[sz].second;
	for(int i = sz - 1, j = ctr - 1; i >= 0; --i)
	{
		for(LL sigma = seq[ord[j]].sig; j >= 0 && seq[ord[j]].sig == sigma; --j)
			if(fir[ord[j]].first <= limit)
			{
				pat = seq[ord[j]];
				dfs(0, 1, 0);
			}
		LL cx = val[i].first, cy = val[i].second;
		if(cx < px && cy < px)
		{
			px = cx;
			py = cy;
		}
		else if(cx < px)
		{
			py = px;
			px = cx;
		}
		else if(cx < py)
			py = cx;
		if(limit > val[sz].second)
		{
			limit = val[sz].second;
			for(int k = 0; k < tot; ++k)
				plim[k] = limit / pr[k];
		}
	}
	std::sort(out, out + osz);
	int kth;
	scanf("%d", &kth);
	printf("%I64d\n", kth <= osz ? out[kth - 1] : -1);
	return 0;
}
