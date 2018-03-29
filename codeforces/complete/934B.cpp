#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
	scanf("%d", &n);
	if(n <= 36) {
		for(int i = 0; i < (n + 1) >> 1; ++i)
			putchar('8' + (i < (n & 1)));
		putchar('\n');
	} else {
		puts("-1");
	}
	return 0;
}
