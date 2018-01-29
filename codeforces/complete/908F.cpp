#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)3e5 + 1;
const char *pat = "RGB";
int sz[3], seq[3][maxn];
int main() {
	int n;
	scanf("%d", &n);
	while(n--) {
		int x;
		char typ;
		scanf("%d %c", &x, &typ);
		for(int i = 0; pat[i]; ++i)
			if(pat[i] == typ)
				seq[i][sz[i]++] = x;
	}
	int res = 0;
	if(!sz[1]) {
		if(sz[0])
			res += seq[0][sz[0] - 1] - seq[0][0];
		if(sz[2])
			res += seq[2][sz[2] - 1] - seq[2][0];
	} else {
		int i = 0, j = 0, k = 0;
		if(i < sz[0] && seq[0][i] < seq[1][j]) {
			res += seq[1][j] - seq[0][i];
			for( ; i < sz[0] && seq[0][i] < seq[1][j]; ++i);
		}
		if(k < sz[2] && seq[2][k] < seq[1][j]) {
			res += seq[1][j] - seq[2][k];
			for( ; k < sz[2] && seq[2][k] < seq[1][j]; ++k);
		}
		for( ; j + 1 < sz[1]; ++j) {
			int mx0 = 0, mx1 = seq[1][j + 1] - seq[1][j], mx2 = 0;
			if(i < sz[0] && seq[0][i] < seq[1][j + 1]) {
				mx0 = std::max(mx0, seq[0][i] - seq[1][j]);
				for( ; i + 1 < sz[0] && seq[0][i + 1] < seq[1][j + 1]; ++i)
					mx0 = std::max(mx0, seq[0][i + 1] - seq[0][i]);
				mx0 = std::max(mx0, seq[1][j + 1] - seq[0][i++]);
			} else
				mx0 = mx1;
			if(k < sz[2] && seq[2][k] < seq[1][j + 1]) {
				mx2 = std::max(mx2, seq[2][k] - seq[1][j]);
				for( ; k + 1 < sz[2] && seq[2][k + 1] < seq[1][j + 1]; ++k)
					mx2 = std::max(mx2, seq[2][k + 1] - seq[2][k]);
				mx2 = std::max(mx2, seq[1][j + 1] - seq[2][k++]);
			} else
				mx2 = mx1;
			if(mx1 < mx0 + mx2)
				res += mx1 * 3 - mx0 - mx2;
			else
				res += mx1 * 2;
		}
		if(i < sz[0])
			res += seq[0][sz[0] - 1] - seq[1][j];
		if(k < sz[2])
			res += seq[2][sz[2] - 1] - seq[1][j];
	}
	printf("%d\n", res);
	return 0;
}
