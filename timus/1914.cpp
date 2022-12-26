#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 101, maxm = 40, maxt = 5, mod[maxm] = {
	1003993313, 1004691293, 1006487081, 1007999977, 1009827023,
	1009970317, 1011720587, 1011837341, 1011884179, 1016137711,
	1021772651, 1026776683, 1028007073, 1028327159, 1028409443,
	1028511833, 1029876853, 1030055111, 1031356913, 1031447861,
	1032359257, 1034933593, 1035711359, 1036801771, 1039784059,
	1043803157, 1048439129, 1049288971, 1054914431, 1056497987,
	1056807623, 1061478157, 1064846407, 1065098269, 1067963803,
	1068581939, 1069179773, 1069293781, 1069585189, 1070961491,
};

int modInv(int x, int m) {
	int y = m, u = 1, v = 0, q;
	while(x) {
		q = y / x;
		y -= q * x;
		swap(x, y);
		v -= q * u;
		swap(u, v);
	}
	assert(y == 1);
	return v < 0 ? v + m : v;
}

int det(int n, int m, int in[][maxn]) {
	int ret = 1;
	static int mat[maxn][maxn];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			(mat[i][j] = in[i][j]) < 0 && (mat[i][j] += m);
	for(int i = 0; i < n; ++i) {
		int k = -1;
		for(int j = i; j < n; ++j)
			if(mat[j][i] && (k == -1 || mat[j][i] < mat[k][i]))
				k = j;
		if(k == -1)
			return 0;
		ret = (LL)ret * mat[k][i] % m;
		if(i < k)
			ret = m - ret;
		int ivs = modInv(mat[k][i], m), tmp;
		for(int j = i; j < n; ++j) {
			tmp = (LL)mat[k][j] * ivs % m;
			mat[k][j] = mat[i][j];
			mat[i][j] = tmp;
		}
		for(int j = i + 1; j < n; ++j) {
			if(!mat[j][i])
				continue;
			tmp = m - mat[j][i];
			for(int k = i; k < n; ++k)
				mat[j][k] = (mat[j][k] + (LL)tmp * mat[i][k]) % m;
		}
	}
	return ret;
}

int main() {
	int n;
	static int mat[maxn][maxn];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%d", mat[i] + j);
	// static mt19937 rnd;
	srand(time(nullptr));
	static int ord[maxm | 1];
	iota(ord, ord + maxm, 0);
	for(int i = 0; i < maxt; ++i) {
		swap(ord[i], ord[rand() % (maxm - i) + i]);
		// swap(ord[i], ord[rnd() % (maxm - i) + i]);
		int m = mod[ord[i]], ret = det(n, m, mat);
		if(ret != 1 && ret != m - 1) {
			puts("Power of magic saves lives");
			return 0;
		}
	}
	puts("Death");
	return 0;
}
