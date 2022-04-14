#include <bits/stdc++.h>
using namespace std;
int main() {
	int idx[257] = {}, c[3][9] = {}, ans = 2;
	idx['m'] = 1;
	idx['p'] = 2;
	idx['s'] = 3;
	for(int i = 0; i < 3; ++i) {
		char buf[3];
		scanf("%s", buf);
		++c[idx[buf[1]] - 1][buf[0] - '1'];
	}
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 9; ++j) {
			ans = min(ans, 3 - c[i][j]);
			if(j + 2 < 9)
				ans = min(ans, 3 - !!c[i][j] - !!c[i][j + 1] - !!c[i][j + 2]);
		}
	printf("%d\n", ans);
	return 0;
}