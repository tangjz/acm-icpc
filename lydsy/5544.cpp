#include <bits/stdc++.h>
const int maxn = 19;
char buf[maxn];
long long f[maxn];
int main() {
	scanf("%s", buf);
	f[0] = 1;
	for(int i = 0; ; ++i)
		if(!buf[i]) {
			printf("%lld\n", f[i]);
			return 0;
		} else {
			int x = buf[i] - '0';
			f[i + 1] = f[i] * (10 - std::abs(9 - x));
			if(i && buf[i - 1] == '1')
				f[i + 1] += f[i - 1] * (10 - std::abs(x + 1));
		}
}