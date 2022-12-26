#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1, mod = (int)1e9 + 7;
int t;
char buf[9][11];
int main() {
	scanf("%d", &t);
	while(t--) {
		for(int i = 0; i < 9; ++i)
			scanf("%s", buf[i]);
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j) {
				int x = i * 3 + j, y = j * 3 + i;
				buf[x][y] = buf[x][y] == '1' ? '2' : '1';
			}
		for(int i = 0; i < 9; ++i)
			printf("%s\n", buf[i]);
	}
	return 0;
}