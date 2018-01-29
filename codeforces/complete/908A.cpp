#include <bits/stdc++.h>
using namespace std;
const int maxn = 51;
const char *pat = "aeiou";
int ans;
char buf[maxn];
int main() {
	scanf("%s", buf);
	for(int i = 0; buf[i]; ++i)
		if(buf[i] >= '0' && buf[i] <= '9')
			ans += (buf[i] - '0') & 1;
		else
			for(int j = 0; pat[j]; ++j)
				ans += buf[i] == pat[j];
	printf("%d\n", ans);
	return 0;
}
