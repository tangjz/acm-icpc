#include <set>
#include <map>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 100010, mod = 1000000007;
int n, fact[maxn], inv[maxn], pw1[maxn], pw2[maxn], ans;
int main()
{
	scanf("%d", &n);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - (LL)mod / i * inv[mod % i] % mod;
	fact[0] = inv[0] = pw1[0] = pw2[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
		pw1[i] = (LL)pw1[i - 1] * 20 % mod;
		pw2[i] = (LL)pw2[i - 1] * 7 % mod;
	}
	for(int i = 1; i <= n; ++i)
		ans = (ans + (LL)fact[n] * inv[i] % mod * inv[n - i] % mod * pw1[i] % mod * pw2[n - i]) % mod;
	printf("%d\n", ans);
	return 0;
}
