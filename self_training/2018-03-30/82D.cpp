#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int n, a[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	if(a[n - 1] == 0) {
		puts("UP");
	} else if(a[n - 1] == 15) {
		puts("DOWN");
	} else if(n > 1) {
		puts(a[n - 2] < a[n - 1] ? "UP" : "DOWN");
	} else {
		puts("-1");
	}
	return 0;
}
