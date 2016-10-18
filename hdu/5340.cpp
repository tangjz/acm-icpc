#include <bitset>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 20010, maxs = ((maxn - 1) >> 6) + 1, maxd = 1 << 4;
int t, n, h[maxn << 1], lbt[1 << maxd];
char str[maxn], buf[maxn << 1 | 1];
struct Bitset
{
	int n;
	size_t len;
	unsigned long long data[maxs];
	void init(int n)
	{
		this -> n = n;
		len = ((n - 1) >> 6) + 1;
		memset(data, 0, len * sizeof data[0]);
	}
	void set(size_t pos)
	{
		data[pos >> 6] |= 1ULL << (pos & 63);
	}
	Bitset operator & (const Bitset &t) const
	{
		Bitset ret = {std::min(n, t.n), std::min(len, t.len)};
		for(size_t i = 0; i < ret.len; ++i)
			ret.data[i] = data[i] & t.data[i];
		return ret;
	}
	void shift_left_one()
	{
		int last = 0, cur;
		for(int i = 0; i < (int)len; ++i)
		{
			cur = (data[i] >> 63) & 1;
			data[i] <<= 1;
			data[i] |= last;
			last = cur;
		}
		++n;
		if(n > (int)(len << 6))
			data[len++] = last;
	}
	void shift_right_one()
	{
		int last = 0, cur;
		for(int i = len - 1; i >= 0; --i)
		{
			cur = data[i] & 1;
			data[i] >>= 1;
			if(last)
				data[i] |= 1ULL << 63;
			last = cur;
		}
		--n;
		if(n <= (int)((len - 1) << 6))
			--len;
	}
	int lowbit() const
	{
		for(int i = 0; i < (int)len; ++i)
			if(data[i])
			{
				unsigned long long tmp = data[i];
				for(int j = 0; j < 4; ++j, tmp >>= maxd)
					if(tmp & ((1 << maxd) - 1))
						return (i << 6) + (j << 4) + lbt[(int)(tmp & ((1 << maxd) - 1))];
			}
		return (int)(~0u >> 1);
	}
} f, g, w;
int main()
{
	for(int i = 1; i < 1 << maxd; ++i)
		lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%s", str);
		n = strlen(str);
		for(int i = 0; i < n; ++i)
		{
			buf[i << 1] = str[i];
			buf[i << 1 | 1] = '#';
		}
		buf[n << 1] = '\0';
		for(int i = 0, mx = 0, id = 0; i <= (n - 1) << 1; ++i)
		{
			h[i] = i < mx ? std::min(mx - i, h[(id << 1) - i]) : 0;
			for( ; h[i] <= i && buf[i - h[i]] == buf[i + h[i]]; ++h[i]);
			if(mx < i + h[i])
			{
				mx = i + h[i];
				id = i;
			}
		}
		f.init(1);
		f.set(0);
		g.init(n);
		for(int i = 0; i < n; ++i)
			if(h[i + n - 1] > n - i - 1)
				g.set(i);
		bool flag = 0;
		for(int i = 0; i <= (n - 1) << 1 && !flag; ++i)
		{
			int k = (h[i] - (i & 1) - (~(i - h[i]) & 1)) >> 1;
			w = f & g;
			w.shift_right_one();
			flag |= w.lowbit() <= k;
			if(i & 1)
			{
				f.shift_left_one();
				if(h[(i + 1) >> 1] > ((i + 1) >> 1))
					f.set(0);
			}
			else
				g.shift_right_one();
		}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}
