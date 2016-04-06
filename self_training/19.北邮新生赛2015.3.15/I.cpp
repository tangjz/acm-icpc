#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 10001;
int t, n, m;
LL sz[maxn << 1], mx[maxn << 1], tag[maxn << 1];
inline void upd(LL &x, LL y)
{
	if(x < y)
		x = y;
}
inline int idx(int L, int R)
{
	return L + R | L != R;
}
void init(int L, int R)
{
	int o = idx(L, R);
	sz[o] = R - L + 1;
	mx[o] = tag[o] = 1;
	if(L == R)
		return;
	int M = L + R >> 1;
	init(L, M);
	init(M + 1, R);
}
void push_down(const int &o, const int &lch, const int &rch)
{
	if(tag[o] == 1)
		return;
	sz[lch] *= tag[o];
	mx[lch] *= tag[o];
	tag[lch] *= tag[o];
	sz[rch] *= tag[o];
	mx[rch] *= tag[o];
	tag[rch] *= tag[o];
	tag[o] = 1;
}
void push_up(const int &o, const int &lch, const int &rch)
{
	sz[o] = sz[lch] + sz[rch];
	mx[o] = max(mx[lch], mx[rch]);
}
pair<int, LL> find(int L, int R, LL res, bool flag) // 0 Left 1 Right
{
	int o = idx(L, R);
	if(L == R)
		return make_pair(L, flag ? res : sz[o] - res + 1);
	int M = L + R >> 1, lch = idx(L, M), rch = idx(M + 1, R);
	push_down(o, lch, rch);
	pair<int, LL> ret;
	if(res <= sz[lch])
		ret = find(L, M, res, flag);
	else
		ret = find(M + 1, R, res - sz[lch], flag);
	push_up(o, lch, rch);
	return ret;
}
void cha_x(int L, int R, int x, LL v)
{
	int o = idx(L, R);
	if(L == R)
	{
		sz[o] += v;
		mx[o] = sz[o];
		return;
	}
	int M = L + R >> 1, lch = idx(L, M), rch = idx(M + 1, R);
	push_down(o, lch, rch);
	if(x <= M)
		cha_x(L, M, x, v);
	else
		cha_x(M + 1, R, x, v);
	push_up(o, lch, rch);
}
void cha_s(int L, int R, int l, int r)
{
	int o = idx(L, R);
	if(l <= L && R <= r)
	{
		sz[o] *= 2;
		mx[o] *= 2;
		tag[o] *= 2;
		return;
	}
	int M = L + R >> 1, lch = idx(L, M), rch = idx(M + 1, R);
	push_down(o, lch, rch);
	if(l <= M)
		cha_s(L, M, l, r);
	if(r > M)
		cha_s(M + 1, R, l, r);
	push_up(o, lch, rch);
}
LL que(int L, int R, int l, int r)
{
	int o = idx(L, R);
	if(l <= L && R <= r)
		return mx[o];
	int M = L + R >> 1, lch = idx(L, M), rch = idx(M + 1, R);
	push_down(o, lch, rch);
	LL ret = 0;
	if(l <= M)
		upd(ret, que(L, M, l, r));
	if(r > M)
		upd(ret, que(M + 1, R, l, r));
	push_up(o, lch, rch);
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		init(1, n);
		while(m--)
		{
			char op[2];
			LL sL, sR;
			pair<int, LL> pL, pR;
			scanf("%s%lld%lld", op, &sL, &sR);
			pL = find(1, n, sL, 0);
			pR = find(1, n, sR, 1);
			if(op[0] == 'D')
			{
				if(pL.first == pR.first)
				{
					cha_x(1, n, pL.first, sR - sL + 1);
					continue;
				}
				cha_x(1, n, pL.first, pL.second);
				cha_x(1, n, pR.first, pR.second);
				if(pL.first + 1 <= pR.first - 1)
					cha_s(1, n, pL.first + 1, pR.first - 1);
			}
			else
			{
				if(pL.first == pR.first)
				{
					printf("%lld\n", sR - sL + 1);
					continue;
				}
				LL res = max(pL.second, pR.second);
				if(pL.first + 1 <= pR.first - 1)
					upd(res, que(1, n, pL.first + 1, pR.first - 1));
				printf("%lld\n", res);
			}
		}
	}
	return 0;
}
