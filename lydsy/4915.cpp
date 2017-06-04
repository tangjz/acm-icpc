#include <cstdio>
#include <algorithm>
typedef long long LL;
LL a, b;
int main() {
	scanf("%lld%lld", &a, &b);
	printf("4\n%lld\n", std::max(b / 11 - a + 1, 0LL) + std::max(b / 29 - a + 1, 0LL));
	return 0;
}
