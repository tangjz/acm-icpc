#include <bits/stdc++.h>
int n, x;
int main() {
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &x);
		if(x) {
			puts("HARD");
			return 0;
		}
	}
	puts("EASY");
	return 0;
}
