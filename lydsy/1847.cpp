#include <cstdio>
const int ans[] = {1, 6, 68, 1170, 27142, 793002, 27914126, 150212803, 326011036, 532422896, 280807462, 964723653, 727302296, 880230970, 871308933, 380032625, 84542615, 677887122, 556092959, 924913504, 456251244, 434430935, 19910633, 995239149, 278341411, 194660221, 879047814, 468374325, 453740976, 24386302};
int main() {
	for(int n; scanf("%d", &n) == 1 && n; printf("%d\n", ans[--n]));
	return 0;
}