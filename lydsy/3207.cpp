/*
 * 长度为N的字符串x~y区间询问长度为K的串匹配
 * 将长度为K的串标号，那么题目转化为区间询问某个数字是否出现
 * 主席树的经典应用，不过我还是写了一个树套树卡时...
 */
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long ULL;
typedef pair<ULL, ULL> Type;
#define x first
#define y second
int ch;
template<typename _> void getint(_ &t)
{
	while((ch = getchar()) < '0' || ch > '9');
	t = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		t = (t << 3) + (t << 1) + ch - '0';
}
const int maxn = 100001, maxk = 21;
multiset<Type> Seg[1 << 18];
ULL a[maxn], b;
Type H[maxn], tmp;
int n, m, k;
void Build(int l, int r, int t)
{
	for(int i = l; i <= r; ++i)
		Seg[t].insert(H[i]);
	if(l == r) return;
	int M = l + r >> 1;
	Build(l, M, t << 1);
	Build(M + 1, r, (t << 1) ^ 1);
}
bool query(int l, int r, int L, int R, int t)
{
	if(l == L && r == R) return Seg[t].find(tmp) != Seg[t].end();
	int M = L + R >> 1;
	if(r <= M) return query(l, r, L, M, t << 1);
	if(l > M) return query(l, r, M + 1, R, (t << 1) ^ 1);
	return query(l, M, L, M, t << 1) || query(M + 1, r, M + 1, R, (t << 1) ^ 1);
}
void Hash()
{
	tmp.x = tmp.y = 0;
	for(int i = 0; i < k; ++i)
	{
		getint(b);
		tmp.x = tmp.x * 13 + b;
		tmp.y = tmp.y * 29 + b;
	}
}
int main()
{
	int l, r;
	getint(n), getint(m), getint(k);
	for(int i = 1; i <= n; ++i)
		getint(a[i]);
	for(int i = 0; i < k; ++i)
		for(int j = 1; j + k - 1 <= n; ++j)
		{
			H[j].x = H[j].x * 13 + a[j + i];
			H[j].y = H[j].y * 29 + a[j + i];
		}
	Build(1, n - k + 1, 1);
	while(m--)
	{
		getint(l), getint(r);
		Hash();
		puts(query(l, r - k + 1, 1, n - k + 1, 1) ? "No" : "Yes");
	}
	return 0;
}
