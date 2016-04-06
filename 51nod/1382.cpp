#include <cstdio>
const int maxn = 131072, INF = 0x3f3f3f3f;
int n, q, tot;
void upd(long long &x, long long y)
{
	if(x <= y)
		x = y;
}
struct Segment
{
	int L, R, M;
	long long val[4];
	Segment *ch[2];
	void init(int, int);
	void merge(Segment, Segment);
	void update(int, int);
	Segment query(int, int);
	long long max();
} __[maxn << 1], *root;
void Segment::init(int l, int r)
{
	L = l;
	R = r;
	M = L + R >> 1;
	if(L == R)
	{
		int x;
		scanf("%d", &x);
		val[0] = val[1] = val[2] = -INF;
		val[3] = x;
		return;
	}
	ch[0] = __ + tot++;
	ch[0] -> init(L, M);
	ch[1] = __ + tot++;
	ch[1] -> init(M + 1, R);
	merge(*ch[0], *ch[1]);
}
void Segment::merge(Segment lch, Segment rch)
{
	for(int i = 0; i < 4; ++i)
	{
		val[i] = -INF;
		for(int j = 0; j < 3; ++j)
		{
			bool flagL = lch.val[(i & 1) | (j & 2)] != -INF, flagR = rch.val[(i & 2) | (j & 1)] != -INF;
			if(flagL)
				upd(val[i], lch.val[(i & 1) | (j & 2)]);
			if(flagR)
				upd(val[i], rch.val[(i & 2) | (j & 1)]);
			if(flagL && flagR)
				upd(val[i], lch.val[(i & 1) | (j & 2)] + rch.val[(i & 2) | (j & 1)]);
		}
	}
}
void Segment::update(int x, int v)
{
	if(L == R)
	{
		val[3] = v;
		return;
	}
	if(x <= M)
		ch[0] -> update(x, v);
	else
		ch[1] -> update(x, v);
	merge(*ch[0], *ch[1]);
}
Segment Segment::query(int l, int r)
{
	if(l <= L && R <= r)
		return *this;
	if(r <= M)
		return ch[0] -> query(l, r);
	if(l > M)
		return ch[1] -> query(l, r);
	Segment tmp = *this;
	tmp.merge(ch[0] -> query(l, r), ch[1] -> query(l, r));
	return tmp;
}
long long Segment::max()
{
	long long ret = -INF;
	for(int i = 0; i < 4; ++i)
		if(ret < val[i])
			ret = val[i];
	return ret;
}
int main()
{
	scanf("%d%d", &n, &q);
	root = __ + tot++;
	root -> init(0, n - 1);
	while(q--)
	{
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		if(t == 1)
			root -> update(x, y);
		else
			printf("%lld\n", (root -> query(x, y)).max());
	}
	return 0;
}
