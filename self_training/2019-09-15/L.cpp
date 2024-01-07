#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = 151, maxd = 8, maxs = 1 << maxd | 1;
ULL table[maxs][maxs];
ULL getPrd(ULL x, ULL y, int dep = 32) {
	if(x > y)
		swap(x, y);
	if(x == 0)
		return 0;
	if(x == 1)
		return y;
	ULL mx = max(x, y);
	assert(!((mx >> dep) >> dep));
	if(mx < 1ULL << maxd && table[x][y])
		return table[x][y];
	for( ; mx < 1ULL << dep; dep >>= 1);
	ULL msk = (1ULL << dep) - 1;
	ULL xL = x & msk, xH = x >> dep;
	ULL yL = y & msk, yH = y >> dep;
	ULL t0 = getPrd(xL, yL, dep >> 1);
	ULL t1 = getPrd(xL ^ xH, yL ^ yH, dep >> 1);
	ULL t2 = getPrd(getPrd(xH, yH, dep >> 1), 1ULL << (dep - 1), dep >> 1);
	if(mx < 1ULL << maxd && !table[x][y])
		return table[x][y] = (t0 ^ t1) << dep | (t0 ^ t2);
	return (t0 ^ t1) << dep | (t0 ^ t2);
}
ULL getInv(ULL x, int dep = 32) { // assert(x);
	static const int BLEN = 64;
	static bitset<BLEN + 1> row[BLEN + 1];
	if(x == 1)
		return 1ULL;
	for( ; x < 1ULL << dep; dep >>= 1);
	dep <<= 1;
	for(int i = 0; i < dep; ++i)
		row[i].reset();
	for(int i = 0; i < dep; ++i) {
		ULL tp = getPrd(x, 1ULL << i);
		for(int j = 0; j < dep; ++j, tp >>= 1)
			if(tp & 1)
				row[j].set(i);
	}
	row[0].set(dep);
	for(int i = 0; i < dep; ++i) {
		for(int j = i; j < dep; ++j)
			if(row[j].test(i)) {
				swap(row[i], row[j]);
				break;
			}
		if(!row[i].test(i))
			continue;
		for(int j = 0; j < dep; ++j)
			if(i != j && row[j].test(i))
				row[j] ^= row[i];
	}
	ULL ret = 0;
	for(int i = dep - 1; i >= 0; --i) {
		if(!row[i].test(i))
			assert(!row[i].test(dep));
		ret = ret << 1 | row[i].test(dep);
	}
	return ret;
}
int n;
ULL mat[maxn][maxn], ans;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%llu", mat[i] + j);
	ans = 1;
	for(int i = 0; i < n; ++i) {
		for(int j = i; j < n; ++j)
			if(mat[j][i]) {
				for(int k = i; k < n; ++k)
					swap(mat[i][k], mat[j][k]);
				break;
			}
		if(!mat[i][i]) {
			ans = 0;
			break;
		}
		ULL ivs = getInv(mat[i][i]);
		for(int j = i; j < n; ++j)
			mat[i][j] = getPrd(mat[i][j], ivs);
		for(int j = i + 1; j < n; ++j) {
			if(!mat[j][i])
				continue;
			ULL prd = mat[j][i];
			for(int k = i; k < n; ++k)
				mat[j][k] ^= getPrd(mat[i][k], prd);
		}
	}
	puts(ans ? "First" : "Second");
	return 0;
}