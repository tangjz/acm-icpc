#include <stdio.h>
typedef long long LL;
const int maxn = 100001, maxs = 1 << 16;
int n, a[maxn], id;
LL f[maxn];
void FWT_iterate(LL x[], int len, int dt) {
	for(int i = 0; i < len; i += dt << 1)
		for(int j = 0; j < dt; ++j) {
			LL t = x[i + dt + j];
			x[i + dt + j] = x[i + j] - t;
			x[i + j] = x[i + j] + t;
		}
}
void FWT(LL x[], int len, int flag) {
	if(flag > 0) {
		for(int i = 1; i < len; i <<= 1)
			FWT_iterate(x, len, i);
	} else {
		for(int i = len >> 1; i > 0; i >>= 1)
			FWT_iterate(x, len, i);
		for(int i = 0; i < len; ++i)
			x[i] /= len;
	}
}
int main()
{
	scanf("%d", &n);
	++f[0];
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		++f[a[i] ^= a[i - 1]];
	}
	FWT(f, maxs, 1);
	for(int i = 0; i < maxs; ++i)
		f[i] *= f[i];
	FWT(f, maxs, -1);
	f[0] -= n + 1;
	for(int i = 1; i < maxs; ++i)
		if(f[id] < f[i])
			id = i;
	printf("%d %lld\n", id, f[id] >> 1);
	return 0;
}
