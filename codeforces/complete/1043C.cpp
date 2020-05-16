#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 9;
char buf[maxn];
int main() {
	scanf("%s", buf);
	for(int i = 0; buf[i]; ++i) {
		if(i)
			putchar(' ');
		char nxt = buf[i + 1] ? buf[i + 1] : 'b';
		putchar(buf[i] == nxt ? '0' : '1');
	}
	putchar('\n');
	return 0;
}