#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int tot, pr[maxn], d[maxn];
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int mx = 0, a, b;
	for(int i = -999; i <= 999; ++i)
		for(int j = -1000; j <= 1000; ++j) {
			int tp = 0;
			while(1) {
				int idx = (tp + i) * tp + j;
				assert(idx < maxn);
				if(idx < 0 || d[idx] != idx)
					break;
				++tp;
			}
			if(mx < tp) {
				mx = tp;
				a = i;
				b = j;
			}
		}
	printf("%d %d: %d (%d)\n", a, b, mx, a * b);
	return 0;
}
