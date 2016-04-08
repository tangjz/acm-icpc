/*
 * 把数先化简 再把常数部分全部剥离 然后求离散对数即可 
 */
#include <map>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long LL;
const int INF = ~0u >> 1, maxn = 1000010;
int A, B, P, ans = INF;
map<int, int> q;
int pow(int x, int n) { LL S = 1, T = x; while(n) { if(n & 1) S = S * T % P; T = T * T % P; n >>= 1; } return S; }
char tmp[4][maxn];
inline int scan(char *tmp, int mod) { LL x = 0; for(int i = 0; tmp[i]; ++i) x = ((x << 3) + (x << 1) + tmp[i] - '0') % mod; return x; }
int main()
{
	scanf("%s%s%s%s%d", tmp[0], tmp[1], tmp[2], tmp[3], &P);
	int a = scan(tmp[0], P - 1), b = scan(tmp[1], P - 1), c = scan(tmp[2], P), g = scan(tmp[3], P);
	A = pow(g, a);
	B = (int)((LL)pow(pow(g, b), P - 2) * c % P);
	int x = (int)sqrt(P);
	for(int i = 0, t = 1; i < x; ++i) { q[t] = i; t = (int)((LL)t * A % P); }
	for(int i = 0, y = P / x, dx = 1, delta = pow(pow(A, x), P - 2); i <= y; ++i)
	{
		if(q.count((int)((LL)dx * B % P))) { ans = i * x + q[(int)((LL)dx * B % P)]; break; }
		dx = (int)((LL)dx * delta % P);
	}
	ans == INF ? puts("no solution") : printf("%d\n", ans);
}
