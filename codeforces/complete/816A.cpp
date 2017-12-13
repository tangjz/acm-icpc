#include <cstdio>
int hh, mm, ans;
int main() {
	for(scanf("%d:%d", &hh, &mm); hh / 10 + hh % 10 * 10 != mm; (++mm) == 60 && (mm = 0, ++hh) == 24 && (hh = 0), ++ans);
	printf("%d\n", ans);
	return 0;
}
