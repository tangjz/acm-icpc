#include <cstdio>
#include <cstring>
typedef unsigned long long ULL;
const int maxs = 1567, maxp = 1 << 16;
int hbit[maxp];
struct Bitset
{
	ULL data[maxs];
	void clear(int size = maxs)
	{
		memset(data, 0, size * sizeof(ULL));
	}
	Bitset operator ^= (const Bitset &t)
	{
		for(int i = 0; i < maxs; ++i)
			data[i] ^= t.data[i];
		return *this;
	}
	void shift(const int &t, Bitset &ret) const
	{
		int dx = t >> 6, dy = t & ((1 << 6) - 1);
		for(int i = 0; i + dx < maxs; ++i)
		{
			ret.data[i + dx] |= data[i] << dy;
			if(i + dx + 1 < maxs && dy)
				ret.data[i + dx + 1] |= data[i] >> ((1 << 6) - dy);
		}
	}
	int highbit() const
	{
		for(int i = maxs - 1; i >= 0; --i)
			if(data[i])
				return (i << 6) + (
				data[i] >> 48 ? hbit[data[i] >> 48] + 48 :
				data[i] >> 32 ? hbit[(data[i] >> 32) & ((1 << 16) - 1)] + 32 :
				data[i] >> 16 ? hbit[(data[i] >> 16) & ((1 << 16) - 1)] + 16 :
								hbit[data[i] & ((1 << 16) - 1)]);
		return -1;
	}
	void print() const
	{
		int deg = highbit();
		if(deg == -1)
		{
			puts("0 0");
			return;
		}
		printf("%d ", deg);
		for(int i = 0; i <= deg; ++i)
			printf("%d%c", (int)((data[i >> 6] >> (i & ((1 << 6) - 1))) & 1), " \n"[i == deg]);
	}
} A[2], B[2], R[2], tmp;
int t, pre = 1, cur, deg;
int main()
{
	for(int i = 2; i < maxp; ++i)
		hbit[i] = hbit[i >> 1] + 1;
	scanf("%d", &t);
	while(t--)
	{
		A[cur].clear();
		A[cur].data[0] |= 1;
		B[cur].clear();
		R[cur].clear();
		scanf("%d", &deg);
		for(int i = 0, x; i <= deg; ++i)
		{
			scanf("%d", &x);
			if(x == 1)
				R[cur].data[i >> 6] |= 1LL << (i & ((1 << 6) - 1));
		}
		pre ^= 1;
		cur ^= 1;
		A[cur].clear();
		B[cur].clear();
		B[cur].data[0] |= 1;
		R[cur].clear();
		scanf("%d", &deg);
		for(int i = 0, x; i <= deg; ++i)
		{
			scanf("%d", &x);
			if(x == 1)
				R[cur].data[i >> 6] |= 1LL << (i & ((1 << 6) - 1));
		}
		while(1)
		{
			pre ^= 1;
			cur ^= 1;
			int pDeg = R[pre].highbit();
			if(pDeg == -1)
				break;
			for(int cDeg = R[cur].highbit(); cDeg >= pDeg; cDeg = R[cur].highbit())
			{
				int diff = cDeg - pDeg;
				tmp.clear();
				A[pre].shift(diff, tmp);
				A[cur] ^= tmp;
				tmp.clear();
				B[pre].shift(diff, tmp);
				B[cur] ^= tmp;
				tmp.clear();
				R[pre].shift(diff, tmp);
				R[cur] ^= tmp;
			}
		}
		A[cur].print();
		B[cur].print();
	}
	return 0;
}
