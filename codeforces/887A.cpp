#include <bits/stdc++.h>
using namespace std;
int i, n;
char buf[111];
int main() {
	scanf("%s", buf);
	for( ; buf[i] && buf[i] != '1'; ++i);
	for( ; buf[i]; n += buf[i++] == '0');
	puts(n < 6 ? "no" : "yes");
	return 0;
}
