#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1;
char buf[maxn];
int main() {
	scanf("%s", buf);
	printf("%s", buf);
	reverse(buf, buf + strlen(buf));
	printf("%s\n", buf);
	return 0;
}
