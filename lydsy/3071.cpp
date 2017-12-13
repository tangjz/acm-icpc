#include <cstdio>
int main() {
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", n * (n - 3) + 3);
	}
	return 0;
}
