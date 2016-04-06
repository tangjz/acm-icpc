#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 50;
int n, ans;
string a[maxn];
int sqr(int x)
{
	return x * x;
}
int lcp(string &a, string &b)
{
	int i, la = a.length(), lb = b.length();
	for(i = 0; i < la && i < lb; ++i)
		if(a[i] != b[i])
			return i;
	return i;
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 0; i < n; ++i)
	{
		cin >> a[i];
		ans += (i < 2 ? 1 : 2) * sqr(a[i].length());
	}
	ans += sqr(lcp(a[0], a[1]));
	sort(a, a + n);
	for(int i = 0; i < n; ++i)
		ans -= sqr(lcp(a[i], a[(i + 1) % n]));
	cout << ans << endl;
	return 0;
}
