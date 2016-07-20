#include <cstdio>
#include <cstring>
const int maxn = 1000001;
int tt, n, m, seg[maxn << 1];
char s[maxn], t[maxn];
inline int seg_idx(int L, int R)
{
	return L + R | L < R;
}
void build(int L, int R)
{
	int rt = seg_idx(L, R);
	if(L == R)
	{
		seg[rt] = s[L] == t[L];
		//printf("set %d : %d\n", L, seg[rt]);
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	build(L, M);
	build(M + 1, R);
	seg[rt] = seg[lch] + seg[rch];
}
void update(int L, int R, int x)
{
	int rt = seg_idx(L, R);
	if(L == R)
	{
		seg[rt] = s[L] == t[L];
		//printf("set %d : %d\n", L, seg[rt]);
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		update(L, M, x);
	else
		update(M + 1, R, x);
	seg[rt] = seg[lch] + seg[rch];
}
int sum(int L, int R, int x)
{
	int rt = seg_idx(L, R);
	if(R <= x)
		return seg[rt];
	int M = L + R >> 1;
	if(x <= M)
		return sum(L, M, x);
	else
		return seg[seg_idx(L, M)] + sum(M + 1, R, x);
}
int query(int L, int R, int s1, int s2)
{
	int rt = seg_idx(L, R);
	if(L == R)
		return L;
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	//printf("check %d : %d %d\n", M, s1 + M, s2 + seg[lch]);
	if(s1 + M + 1 > s2 + seg[lch] + (s[M + 1] == t[M + 1]))
		return query(L, M, s1, s2);
	else
		return query(M + 1, R, s1, s2 + seg[lch]);
}
int main()
{
	scanf("%d", &tt);
	for(int Case = 1; Case <= tt; ++Case)
	{
		scanf("%s%s%d", s, t, &m);
		n = strlen(s);
		build(0, n - 1);
		printf("Case %d:\n", Case);
		while(m--)
		{
			int typ, x, y;
			char ch;
			scanf("%d", &typ);
			if(typ == 1)
			{
				scanf("%d%d %c", &x, &y, &ch);
				if(x == 1)
					s[y] = ch;
				else
					t[y] = ch;
				update(0, n - 1, y);
			}
			else
			{
				scanf("%d", &x);
				if(s[x] == t[x])
				{
					int val = (x ? sum(0, n - 1, x - 1) : 0) - (x - 1);
					//printf("sum %d : %d\n", x - 1, val);
					printf("%d\n", query(0, n - 1, val, 0) - x + 1);
				}
				else
					puts("0");
			}
		}
	}
	return 0;
}
