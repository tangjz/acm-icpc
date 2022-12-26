#include <cstdio>

int n, k;

int gcd(int a, int b) {
	for (int c; b; c = a % b, a = b, b = c);
	return a;
}

int main() {
	scanf("%d%d", &n, &k);
	printf("%d\n", gcd(n,k));
	return 0;
}
