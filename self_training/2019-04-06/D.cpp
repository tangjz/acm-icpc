#include <bits/stdc++.h>
using namespace std;
const int maxn = 1 << 10 | 1;
int t, n, m, d, msk[maxn];
char buf[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d%d", &n, &m, &d);
		memset(msk, 0, (n - m) * sizeof(int));
		for(int i = 0; i < d; ++i) {
			for(int j = 0; j < n; ++j)
				buf[j] = "01"[(j >> i) & 1];
			buf[n] = '\0';
			printf("%s\n", buf);
			fflush(stdout);
			scanf("%s", buf);
			if(!strcmp(buf, "-1"))
				exit(0);
			for(int j = 0; j < n - m; ++j)
				msk[j] |= (buf[j] == '1') << i;
		}
		const int BMSK = (1 << d) - 1;
		int cnt = 0;
		for(int i = 0; i < n; ++i) {
			if(i - cnt < n - m && msk[i - cnt] == (i & BMSK))
				continue;
			assert(cnt < m);
			if((cnt++) > 0)
				printf(" ");
			printf("%d", i);
		}
		assert(cnt == m);
		printf("\n");
		fflush(stdout);
		scanf("%s", buf);
		if(strcmp(buf, "1")) {
			fprintf(stderr, "Case #%d: failed [resp=\"%s\"]\n", Case, buf);
			exit(0);
		}
	}
	return 0;
}