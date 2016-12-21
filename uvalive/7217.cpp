#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100001;
int t, n, low, high, a[maxn], b[5], c[5], sz, seq[maxn];
bool chkPos()
{
	if(n - b[2] < low)
		return 0;
	int cnt = 0;
	memset(c, 0, sizeof c);
	{ // add double -2
		int tmp = std::min(high - cnt, b[0] - c[0]) >> 1;
		c[0] += tmp << 1;
		cnt += tmp << 1;
	}
	{ // add 2
		int tmp = std::min(high - cnt, b[4] - c[4]);
		c[4] += tmp;
		cnt += tmp;
	}
	if(c[0] < b[0] && c[1] < b[1] && cnt + 2 <= high)
	{ // add -2 and -1
		++c[0];
		++c[1];
		cnt += 2;
	}
	if(cnt < low)
	{ // add double -1
		int tmp = std::min(high - cnt, b[1] - c[1]) >> 1;
		c[1] += tmp << 1;
		cnt += tmp << 1;
	}
	if(cnt < low)
	{ // add 1
		int tmp = std::min(high - cnt, b[3] - c[3]);
		c[3] += tmp;
		cnt += tmp;
	}
	if(cnt < low) // 1 to -1
	{ // modify to add -2 and -1 or double -1
		if(c[3] > 0 && c[0] < b[0] && c[1] < b[1])
		{
			--c[3];
			++c[0];
			++c[1];
			++cnt;
		}
		int tmp = std::min(high - cnt, std::min(c[3], (b[1] - c[1]) >> 1));
		c[3] -= tmp;
		c[1] += tmp << 1;
		cnt += tmp;
	}
	if(cnt < low) // 2 to -1
	{ // modify to add -2 and -1 or double -1
		if(c[4] > 0 && c[0] < b[0] && c[1] < b[1])
		{
			--c[4];
			++c[0];
			++c[1];
			++cnt;
		}
		int tmp = std::min(high - cnt, std::min(c[4], (b[1] - c[1]) >> 1));
		c[4] -= tmp;
		c[1] += tmp << 1;
		cnt += tmp;
	}
	return cnt >= low;
}
void chkZero() // always have solution
{
	int cnt = 0;
	memset(c, 0, sizeof c);
	{ // add 0
		int tmp = std::min(high - cnt, b[2] - c[2]);
		c[2] += tmp;
		cnt += tmp;
	}
	for(int i = 0; i < 5 && cnt < low; ++i)
	{ // add others
		if(i == 2)
			continue;
		int tmp = std::min(high - cnt, b[i] - c[i]);
		c[i] += tmp;
		cnt += tmp;
	}
}
void chkNeg()
{
	int cnt = 0;
	memset(c, 0, sizeof c);
	{ // add neg
		int idx = c[1] < b[1] ? 1 : 0;
		++c[idx];
		++cnt;
	}
	{ // add double -1
		int tmp = std::min(high - cnt, b[1] - c[1]) >> 1;
		c[1] += tmp << 1;
		cnt += tmp << 1;
	}
	{ // add 1
		int tmp = std::min(high - cnt, b[3] - c[3]);
		c[3] += tmp;
		cnt += tmp;
	}
	if(cnt < low && c[0] < b[0] && c[1] < b[1] && cnt + 2 <= high)
	{ // add -2 and -1
		++c[0];
		++c[1];
		cnt += 2;
	}
	if(cnt < low)
	{ // add double -2
		int tmp = std::min(low - cnt + (low < high), b[0] - c[0]) >> 1;
		c[0] += tmp << 1;
		cnt += tmp << 1;
	}
	if(cnt < low)
	{ // add 2
		int tmp = std::min(low - cnt, b[4] - c[4]);
		c[4] += tmp;
		cnt += tmp;
	}
	if(cnt < low) // 1 to -2
	{ // modify to add -2 and -1 or double -2
		if(c[3] > 0 && c[0] < b[0] && c[1] < b[1])
		{
			--c[4];
			++c[0];
			++c[1];
			++cnt;
		}
		int tmp = std::min(low - cnt, std::min(c[3], (b[1] - c[1]) >> 1));
		c[3] -= tmp;
		c[1] += tmp << 1;
		cnt += tmp;
	}
	if(cnt < low) // 2 to -2
	{ // modify to add -2 and -1 or double -2
		if(c[4] > 0 && c[0] < b[0] && c[1] < b[1])
		{
			--c[4];
			++c[0];
			++c[1];
			++cnt;
		}
		int tmp = std::min(low - cnt, std::min(c[4], (b[1] - c[1]) >> 1));
		c[4] -= tmp;
		c[1] += tmp << 1;
		cnt += tmp;
	}
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d", &n, &low, &high);
		memset(b, 0, sizeof b);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			++b[a[i] + 2];
		}
		if(!chkPos())
			b[2] > 0 ? chkZero() : chkNeg();
		sz = 0;
		for(int i = 1; i <= n; ++i)
			if(c[a[i] + 2] > 0)
			{
				seq[++sz] = i;
				--c[a[i] + 2];
			}
		printf("Case #%d:\n%d\n", Case, sz);
		for(int i = 1; i <= sz; ++i)
			printf("%d%c", seq[i], " \n"[i == sz]);
	}
	return 0;
}
