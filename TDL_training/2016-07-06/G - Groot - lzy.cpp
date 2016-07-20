#include <cstdio>

int n;
char s[1000009];

int main() {
	gets(s);
	for (const char *t = s; *t; ++t) n += *t == '!';
	if (n) {
		putchar('W');
		while (n--) putchar('o');
		puts("w");
	} else {
		puts("Pfff");
	}
	return 0;
}
