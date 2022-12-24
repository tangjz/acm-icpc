#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 11, maxl = 1673, maxs = maxl * 18 + 1;
const LL maxv = (LL)1e18;
int t, a[maxn], ord[maxn], len;
char buf[maxn][maxs];
LL num[maxl];
int main() {
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i) {
		scanf("%d", a + i);
		ord[i] = i;
		for(int j = 1; j < i; ++j)
			if(a[ord[j]] > a[ord[i]]) {
				rotate(ord + j, ord + i, ord + i + 1);
				break;
			}
	}
	len = 1;
	num[0] = 2;
	for(int i = 1; i <= t; ++i) {
		for(int dt = a[ord[i]] - a[ord[i - 1]]; dt--; ) {
			for(int j = 0; j < len; ++j)
				num[j] <<= 1;
			for(int j = 0; j < len; ++j)
				if(num[j] >= maxv) {
					num[j] -= maxv;
					++num[j + 1];
				}
			if(num[len])
				++len;
		}
		LL rem = 0;
		char *ptr = buf[ord[i]];
		for(int j = len - 1; j >= 0; --j) {
			rem = rem * maxv + num[j];
			ptr += sprintf(ptr, "%018lld", rem / 3);
			rem %= 3;
		}
		*ptr = '\0';
	}
	for(int i = 1; i <= t; ++i) {
		char *ptr = buf[i];
		for( ; *ptr == '0'; ++ptr);
		puts(ptr);
	}
	return 0;
}