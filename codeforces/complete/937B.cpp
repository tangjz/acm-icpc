#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int p, y;
int main() {
	scanf("%d%d", &p, &y);
	for( ; p < y; --y) {
		bool chk = 1;
		for(int i = 2; i <= p && i * i <= y; ++i)
			if(y % i == 0) {
				chk = 0;
				break;
			}
		if(chk) {
			printf("%d\n", y);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
