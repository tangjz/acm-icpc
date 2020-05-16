#include <bitset>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 105, maxm = 1000010;
int val[maxn];
bitset<maxm> idx[maxn];
int n, a[maxn], b[maxn], mx, f[maxm];
bool flag;
char out[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i <= n; ++i)
	{
		scanf("%d", a + i);
		mx += a[i];
	}
	mx -= a[0];
	if(mx > a[0])
		mx = a[0];
	for(int i = 0; i <= n; ++i)
		scanf("%d", b + i);
	// calc max (sum < p && sum < q)
	memset(f, -1, sizeof f);
	f[0] = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = mx; j >= a[i]; --j)
		{
			if(f[j - a[i]] == -1)
				continue;
			if(f[j] == -1 || f[j] < f[j - a[i]] + b[i])
				f[j] = f[j - a[i]] + b[i];
		}
	flag = 1;
	for(int i = 0; i <= mx && i < a[0]; ++i)
	{
		if(f[i] == -1)
			continue;
		if(f[i] >= b[0])
		{
			flag = 0;
			mx = i; // construct sum = mx
			break;
		}
	}
	if(!flag)
	{
		memset(f, -1, sizeof f);
		f[0] = 0;
		for(int i = 1; i <= n; ++i)
		{
			idx[i].reset();
			for(int j = mx; j >= a[i]; --j)
			{
				if(f[j - a[i]] == -1)
					continue;
				if(f[j] == -1 || f[j] < f[j - a[i]] + b[i])
				{
					f[j] = f[j - a[i]] + b[i];
					idx[i].set(j);
				}
			}
		}
		puts("NO");
		for(int i = n, o = mx; i >= 1; --i)
		{
			out[i - 1] = '0' + idx[i].test(o);
			if(out[i - 1] == '1')
				o -= a[i];
		}
		out[n] = '\0';
		puts(out);
		return 0;
	}
	// calc min (sum >= p && sum >= q)
	if(mx < a[0])
	{
		puts("YES");
		return 0;
	}
	memset(f, -1, sizeof f);
	f[0] = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = mx + a[i]; j >= a[i]; --j)
		{
			if(f[j - a[i]] == -1)
				continue;
			int k = j <= mx ? j : mx;
			if(f[k] == -1 || f[k] > f[j - a[i]] + b[i])
				f[k] = f[j - a[i]] + b[i];
		}
	flag = 1;
	int pos;
	for(int i = a[0]; i <= mx; ++i)
	{
		if(f[i] == -1)
			continue;
		if(f[i] < b[0])
		{
			flag = 0;
			pos = i; // construct sum = pos
			break;
		}
	}
	if(!flag)
	{
		memset(f, -1, sizeof f);
		f[0] = 0;
		for(int i = 1; i <= n; ++i)
		{
			idx[i].reset();
			for(int j = mx + a[i]; j >= a[i]; --j)
			{
				if(f[j - a[i]] == -1)
					continue;
				int k = j <= mx ? j : mx;
				if(f[k] == -1 || f[k] > f[j - a[i]] + b[i])
				{
					f[k] = f[j - a[i]] + b[i];
					idx[i].set(k);
					if(k == mx)
						val[i] = j - a[i];
				}
			}
		}
		puts("NO");
		for(int i = n, o = pos; i >= 1; --i)
		{
			out[i - 1] = '0' + idx[i].test(o);
			if(out[i - 1] == '1')
			{
				if(o == mx)
					o = val[i];
				else
					o -= a[i];
			}
		}
		out[n] = '\0';
		puts(out);
		return 0;
	}
	puts("YES");
	return 0;
}
