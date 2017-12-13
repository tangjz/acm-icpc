#include <bits/stdc++.h>
using namespace std;
const int maxn = 25, maxm = 7, rot[maxm][maxn] = {
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
{0, 2, 4, 1, 3, 13, 14, 7, 8, 9, 10, 11, 12, 21, 22, 15, 16, 5, 6, 19, 20, 17, 18, 23, 24},
{0, 1, 2, 3, 4, 5, 6, 15, 16, 11, 9, 12, 10, 13, 14, 23, 24, 17, 18, 7, 8, 21, 22, 19, 20},
{0, 1, 23, 3, 21, 5, 2, 7, 4, 9, 6, 11, 8, 13, 14, 15, 16, 18, 20, 17, 19, 12, 22, 10, 24},
{0, 5, 2, 7, 4, 9, 6, 11, 8, 24, 10, 22, 12, 14, 16, 13, 15, 17, 18, 19, 20, 21, 3, 23, 1},
{0, 1, 2, 16, 14, 7, 5, 8, 6, 19, 17, 11, 12, 13, 9, 15, 10, 3, 18, 4, 20, 21, 22, 23, 24},
{0, 15, 13, 3, 4, 5, 6, 7, 8, 9, 10, 20, 18, 11, 14, 12, 16, 17, 1, 19, 2, 22, 24, 21, 23}};
int col[maxn], nxt[maxn];
bool valid() {
	for(int i = 1; i < maxn; i += 4)
		if(!(nxt[i] == nxt[i + 1] && nxt[i + 1] == nxt[i + 2] && nxt[i + 2] == nxt[i + 3]))
			return 0;
	return 1;
}
int main() {
	for(int i = 1; i < maxn; ++i)
		scanf("%d", col + i);
	for(int i = 1; i < maxm; ++i) {
		for(int j = 1; j < maxn; ++j)
			nxt[j] = col[rot[i][j]];
		if(valid()) {
			puts("YES");
			return 0;
		}
		for(int j = 1; j < maxn; ++j)
			nxt[rot[i][j]] = col[j];
		if(valid()) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
