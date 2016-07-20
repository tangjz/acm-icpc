#include <cstdio>
#include <cstring>

int n, m, c[1009];
char suff[1009][209];
char s[209], *t;

int find(char t[]) {
	for (int i = 0; i < m; ++i) if (strcmp(suff[i], t) == 0) return i;
	strcpy(suff[m], t);
	return m++;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	while (n--) {
		scanf("%s", s);
		for (t = s; *t != '.'; ++t);
		++c[find(++t)];
	}
	for (int i = 0; i < m; ++i)
		printf("%s: %d\n", suff[i], c[i]);
	return 0;
}
