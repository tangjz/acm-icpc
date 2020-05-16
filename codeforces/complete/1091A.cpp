#include <bits/stdc++.h>
using namespace std;
int a, b, c;
int main() {
	scanf("%d%d%d", &a, &b, &c);
	a = min(a, min(b - 1, c - 2));
	printf("%d\n", a + a + 1 + a + 2);
	return 0;
}