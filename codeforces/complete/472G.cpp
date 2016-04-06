#include <cstdio>
#include <cstring>
const int maxn = 200001, mod = (1 << 16) - 1;
int q, p1, p2, len, cnt[1 << 16], ans;
unsigned int bitA[32][maxn >> 5], bitB[32][maxn >> 5], *it, *jt;
char A[maxn], B[maxn];
inline int popcnt(unsigned int x)
{
	return cnt[x >> 16] + cnt[x & mod];
}
int main()
{
	scanf("%s%s%d", A, B, &q);
	for(int i = 1; i < 1 << 16; ++i)
		cnt[i] = cnt[i >> 1] + (i & 1);
	for(int i = 0; i < 32; ++i)
		for(int j = 0; A[i + j]; ++j)
			if(A[i + j] == '1')
				bitA[i][j >> 5] |= 1 << (j & 31);
	for(int i = 0; i < 32; ++i)
		for(int j = 0; B[i + j]; ++j)
			if(B[i + j] == '1')
				bitB[i][j >> 5] |= 1 << (j & 31);
	while(q--)
	{
		scanf("%d%d%d", &p1, &p2, &len);
		for(ans = 0, it = bitA[p1 & 31] + (p1 >> 5), jt = bitB[p2 & 31] + (p2 >> 5); len >= 32; len -= 32)
			ans += popcnt(*(it++) ^ *(jt++));
		ans += popcnt((*it ^ *jt) & ((1 << len) - 1));
		printf("%d\n", ans);
	}
	return 0;
}
