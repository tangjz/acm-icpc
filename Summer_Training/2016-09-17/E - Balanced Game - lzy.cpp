#include <cstdio>

int T, n;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		puts(n & 1 ? "Balanced" : "Bad");
	}
	return 0;
}
