#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 26;
int n, m;
char buf[maxn];
int main() {
	scanf("%s", buf);
	n = strlen(buf);
	for(int i = 0; i < n && m < maxd; ++i)
		if(buf[i] <= 'a' + m)
			buf[i] = 'a' + (m++);
	if(m < maxd) {
		puts("-1");
	} else {
		puts(buf);
	}
	return 0;
}
