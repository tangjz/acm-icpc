#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)2e5 + 1;

int main() {
	int n;
	scanf("%d", &n);
	vector<int> a(n), b(n);
	for(int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	sort(a.begin(), a.end());
	int tot = 0;
	for(int i = 1; i < n; i += 2)
		b[i] = a[tot++];
	for(int i = 0; i < n; i += 2)
		b[i] = a[tot++];
	pair<int, int> low = {abs(b[0] - b[n - 1]), 0};
	for(int i = 1; i < n; ++i)
		low = min(low, make_pair(abs(b[i] - b[i - 1]), i));
	rotate(b.begin(), b.begin() + low.second, b.end());
	for(int i = 0; i < n; ++i)
		printf("%d%c", b[i], " \n"[i == n - 1]);
	return 0;
}