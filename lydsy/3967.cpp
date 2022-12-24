#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxm = 17, pr[maxm] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
const int maxe = 63, maxs = 39911;
const LL maxv = ~0ULL >> 1;
int tot, gcd[maxe][maxe];
pair<LL, LL> seq[maxs];
void dfs(LL x, LL k, int dep, int upp, int sum) {
	if(x > 1)
		seq[tot++] = make_pair(k, x);
	for(int i = 1; i <= upp; ++i) {
		if(x > maxv / pr[dep])
			break;
		int fz = sum + 1, fm = i, com = gcd[fz][fm];
		fz /= com;
		fm /= com;
		if(k / fm > maxv / fz)
			break;
		dfs(x *= pr[dep], k = k / fm * fz, dep + 1, i, ++sum);
	}
}
int main() {
	for(int i = 0; i < maxe; ++i)
		gcd[0][i] = i;
	for(int i = 1; i < maxe; ++i)
		for(int j = 0; j < maxe; ++j)
			gcd[i][j] = i > j ? gcd[j][i] : gcd[i][j - i];
	dfs(1, 1, 0, maxe - 1, 0);
	sort(seq, seq + tot);
	int tp = tot;
	tot = 0;
	for(int i = 0; i < tp; ++i)
		if(!tot || seq[tot - 1].first != seq[i].first)
			seq[tot++] = seq[i];
	for(LL k; scanf("%lld", &k) == 1; printf("%lld %lld\n", k, lower_bound(seq, seq + tot, make_pair(k, 0LL)) -> second));
	return 0;
}
