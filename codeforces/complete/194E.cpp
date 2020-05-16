#include <bits/stdc++.h>
using namespace std;
const char *pat[] = {"abbb", "abaa", "aabb", "aaba", "abab", "abba", "aaab"};
const int mat[][7] = {
	{1, 1, 0, 0, -1, -1, 1},
	{1, 0, -1, 1, 0, -1, 1},
	{-1, 0, 1, 0, 1, 0, -1},
	{0, 1, -1, 1, -1, 0, 1},
	{0, -1, 1, 0, 0, 1, -1},
	{0, 0, 0, -1, 1, 1, -1},
};
int x[7], d[7];
int main() {
	for(int i = 0; i < 6; ++i)
		scanf("%d", d + i);
	int low = 0, upp = ~0u >> 1;
	for(int i = 0; i < 6; ++i) {
		for(int j = 0; j < 6; ++j)
			x[i] += mat[i][j] * d[j];
		if(x[i] & 1) {
			puts("-1");
			return 0;
		}
		x[i] >>= 1;
		if(mat[i][6] < 0) {
			upp = min(upp, x[i]);
		} else {
			low = max(low, -x[i]);
		}
	}
	if(low > upp) {
		puts("-1");
		return 0;
	} else {
		int sum = x[6] = low;
		for(int i = 0; i < 6; ++i) {
			x[i] += mat[i][6] * low;
			sum += x[i];
		}
		printf("%d\n", sum);
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 7; ++j)
				for(int k = 0; k < x[j]; ++k)
					putchar(pat[j][i]);
			putchar('\n');
		}
	}
	return 0;
}