#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1;
int n, mx, ans;
bool vis[maxn];
int main() {
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &mx);
		vis[--mx] = 1;
	}
	for(int i = 1; i <= mx; ++i)
		if(vis[i]) {
			++ans;
			for(int j = i; j <= mx; j += i)
				vis[j] = 0;
		}
	printf("%d\n", max(ans, 1));
	return 0;
}