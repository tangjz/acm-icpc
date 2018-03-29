#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxm = 11;
int m;
LL n, a[maxm];
map<LL, bool> Hash;
bool dfs(LL n) {
	if(Hash.count(n))
		return Hash[n];
	for(int i = 0; i < m; ++i)
		if(n % a[i] == 0 && (!(a[i] & 1) || !dfs(n / a[i])))
			return Hash[n] = 1;
	return Hash[n] = 0;
}
int main() {
	scanf("%lld%d", &n, &m);
	for(int i = 0; i < m; ++i)
		scanf("%lld", a + i);
	puts(dfs(n) ? "First" : "Second");
	return 0;
}
