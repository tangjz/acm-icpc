#include <cstdio>
const int maxn = (int)1e4 + 1;
int main() {
	int n, k, m;
	char buf[maxn];
	scanf("%d%d%d%s", &n, &k, &m, buf);
	int pos = 0, cnt = 0;
	while(m > 0) {
		cnt += !pos;
		int adt = (n + m - pos - 1) / (k + 1) + 1;
		if(adt > m)
			adt = m;
		m -= adt;
		pos = (pos + adt * k) % (n + m);
	}
	printf("%c\n", (buf[pos] - 'A' + cnt) % 26 + 'A');
	return 0;
}