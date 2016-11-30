#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100005, maxm = 6;
int n, m, q, wseg[maxn << 1];
char buf[maxn], str[maxm];
inline int seg_idx(int L, int R)
{
	return L + R | L < R;
}
void wfilp(int L, int R, int l, int r)
{
	if(l <= L && R <= r)
	{
		wseg[seg_idx(L, R)] ^= 1;
		return;
	}
	int M = L + R >> 1;
	if(l <= M)
		wfilp(L, M, l, r);
	if(r > M)
		wfilp(M + 1, R, l, r);
}
int wquery(int L, int R, int x)
{
	int rev = 0;
	while(L < R)
	{
		rev ^= wseg[seg_idx(L, R)];
		int M = L + R >> 1;
		if(x <= M)
			R = M;
		else
			L = M + 1;
	}
	return rev ^ wseg[seg_idx(L, R)];
}
struct Segment
{
	int minv, maxv, tag;
} tseg[maxn << 1];
inline void push_up(int rt, int lch, int rch)
{
	if(tseg[lch].minv == -1 || tseg[rch].minv == -1)
		tseg[rt].minv = std::max(tseg[lch].minv, tseg[rch].minv);
	else
		tseg[rt].minv = std::min(tseg[lch].minv, tseg[rch].minv);
	tseg[rt].maxv = std::max(tseg[lch].maxv, tseg[rch].maxv);
}
inline void push_down(int rt, int lch, int rch)
{
	if(tseg[rt].tag)
	{
		if(tseg[lch].minv != -1)
		{
			std::swap(tseg[lch].minv, tseg[lch].maxv);
			tseg[lch].minv = m - tseg[lch].minv;
			tseg[lch].maxv = m - tseg[lch].maxv;
		}
		tseg[lch].tag ^= 1;
		if(tseg[rch].minv != -1)
		{
			std::swap(tseg[rch].minv, tseg[rch].maxv);
			tseg[rch].minv = m - tseg[rch].minv;
			tseg[rch].maxv = m - tseg[rch].maxv;
		}
		tseg[rch].tag ^= 1;
		tseg[rt].tag = 0;
	}
}
void tinit(int L, int R)
{
	int rt = seg_idx(L, R);
	tseg[rt].tag = 0;
	if(L == R)
	{
		int cnt = 0;
		for(int i = 0; i < m; ++i)
		{
			if(tolower(str[i]) != tolower(buf[L + i]))
			{
				cnt = -1;
				break;
			}
			else if(str[i] != buf[L + i])
				++cnt;
		}
		tseg[rt].minv = tseg[rt].maxv = cnt;
		// printf("match from %d : %d\n", L, cnt);
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	tinit(L, M);
	tinit(M + 1, R);
	push_up(rt, lch, rch);
}
void tflip(int L, int R, int l, int r)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		if(tseg[rt].minv != -1)
		{
			std::swap(tseg[rt].minv, tseg[rt].maxv);
			tseg[rt].minv = m - tseg[rt].minv;
			tseg[rt].maxv = m - tseg[rt].maxv;
		}
		tseg[rt].tag ^= 1;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	push_down(rt, lch, rch);
	if(l <= M)
		tflip(L, M, l, r);
	if(r > M)
		tflip(M + 1, R, l, r);
	push_up(rt, lch, rch);
}
void tupdate(int L, int R, int x, int v)
{
	int rt = seg_idx(L, R);
	if(L == R)
	{
		tseg[rt].minv = tseg[rt].maxv = v;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	push_down(rt, lch, rch);
	if(x <= M)
		tupdate(L, M, x, v);
	else
		tupdate(M + 1, R, x, v);
	push_up(rt, lch, rch);
}
int tquery(int L, int R, int l, int r)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return tseg[rt].maxv;
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R), ret = -1;
	push_down(rt, lch, rch);
	if(l <= M)
		ret = std::max(ret, tquery(L, M, l, r));
	if(r > M)
		ret = std::max(ret, tquery(M + 1, R, l, r));
	push_up(rt, lch, rch);
	return ret;
}
int main()
{
	while(scanf("%d%s%s", &q, str, buf) == 3)
	{
		n = strlen(buf);
		m = strlen(str);
		memset(wseg, 0, (n << 1) * sizeof(int));
		if(n >= m)
			tinit(0, n - m);
		while(q--)
		{
			int l, r;
			scanf("%d%d", &l, &r);
			--l;
			--r;
			printf("%d\n", l <= r - m + 1 ? tquery(0, n - m, l, r - m + 1) : -1);
			// printf("word filp [%d, %d]\n", l, r);
			wfilp(0, n - 1, l, r);
			if(l <= r - m + 1)
			{
				// printf("tag filp [%d, %d]\n", l, r - m + 1);
				tflip(0, n - m, l, r - m + 1);
			}
			{ // modify left
				int wL = l - m + 1 > 0 ? l - m + 1 : 0, wR = l - 1 < n - m ? l - 1 : n - m, state[maxm << 1] = {};
				if(wL <= wR)
				{
					// printf("modify left [%d, %d]\n", wL, wR);
					for(int i = 0; wL + i <= wR + m - 1; ++i)
						state[i] = wquery(0, n - 1, wL + i);
					for(int i = 0; wL + i <= wR; ++i)
					{
						int cnt = 0;
						for(int j = 0; j < m; ++j)
						{
							if(tolower(str[j]) != tolower(buf[wL + i + j]))
							{
								cnt = -1;
								break;
							}
							else if((str[j] == buf[wL + i + j]) == state[i + j])
								++cnt;
						}
						if(cnt != -1)
						{
							// printf("change %d : %d\n", wL + i, cnt);
							tupdate(0, n - m, wL + i, cnt);
						}
					}
				}
			}
			{ // modify right
				int wL = l > r - m + 2 ? l : r - m + 2, wR = r < n - m ? r : n - m, state[maxm << 1] = {};
				if(wL <= wR)
				{
					// printf("modify right [%d, %d]\n", wL, wR);
					for(int i = 0; wL + i <= wR + m - 1; ++i)
						state[i] = wquery(0, n - 1, wL + i);
					for(int i = 0; wL + i <= wR; ++i)
					{
						int cnt = 0;
						for(int j = 0; j < m; ++j)
						{
							if(tolower(str[j]) != tolower(buf[wL + i + j]))
							{
								cnt = -1;
								break;
							}
							else if((str[j] == buf[wL + i + j]) == state[i + j])
								++cnt;
						}
						if(cnt != -1)
						{
							// printf("change %d : %d\n", wL + i, cnt);
							tupdate(0, n - m, wL + i, cnt);
						}
					}
				}
			}
		}
	}
	return 0;
}
