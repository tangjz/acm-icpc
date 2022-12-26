#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
#define x first
#define y second
const int maxn = (int)2e3 + 1, maxd = 26, mod = (int)1e9 + 7;

int main() {
	int t = 1;
	// scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int n, m;
		scanf("%d%d", &n, &m);
		const char *pat = "WRYB";
		const int trI = 9, trRY = 6, trRB = 13, trYB = 11;
		auto trans = [](int lft, int rht) {
			int ret = 0;
			for(int i = 0; i < 4; ++i, lft >>= 1)
				if(lft & 1)
					ret ^= ((rht >> ((i & 1) << 1)) & 3) << (i & 2);
			return ret;
		};
		int row = 0, col = n << 1; // [0..col-1] | [col]
		static int rep[maxn];
		static bitset<maxn> mat[maxn];
		for(int i = 0; i < n; ++i)
			rep[i] = trI;
		while(m--) {
			int cnt, pos;
			static char op[5];
			scanf("%s", op);
			if(op[0] == 'm') {
				mat[row].reset();
				mat[row + 1].reset();
				scanf("%d", &cnt);
				while(cnt--) {
					scanf("%d", &pos);
					--pos;
					for(int i = 0, tmp = rep[pos]; i < 4; ++i, tmp >>= 1)
						if(tmp & 1)
							mat[row + !!(i & 2)].flip(pos << 1 | (i & 1));
				}
				scanf("%s", op);
				int msk;
				for(int i = 0; i < 4; ++i)
					if(pat[i] == op[0]) {
						msk = i;
						break;
					}
				for(int i = 0; i < 2; ++i, msk >>= 1)
					if(msk & 1)
						mat[row + i].flip(col);
				row += 2;
			} else {
				int tr = op[0] == 'R' ? (op[1] == 'Y' ? trRY : trRB) : trYB;
				scanf("%d", &cnt);
				while(cnt--) {
					scanf("%d", &pos);
					--pos;
					rep[pos] = trans(tr, rep[pos]);
				}
			}
		}
		// for(int i = 0; i < row; ++i) {
		// 	static char buf[maxn];
		// 	for(int j = 0; j <= col; ++j)
		// 		buf[j] = "01"[mat[i].test(j)];
		// 	buf[col + 1] = '\0';
		// 	puts(buf);
		// }
		int rk = 0;
		for(int i = 0; i < col; ++i) {
			int pivot = -1;
			for(int j = rk; j < row; ++j)
				if(mat[j].test(i)) {
					pivot = j;
					break;
				}
			if(pivot == -1)
				continue;
			swap(mat[rk], mat[pivot]);
			for(int j = 0; j < row; ++j)
				if(j != rk && mat[j].test(i))
					mat[j] ^= mat[rk];
			++rk;
		}
		bool chk = 1;
		for(int i = rk; chk && i < row; ++i)
			chk &= !mat[i].test(col);
		if(!chk) {
			puts("NO");
		} else {
			puts("YES");
			for(int i = 0; i < n; ++i)
				rep[i] = 0;
			for(int i = 0; i < rk; ++i) {
				if(!mat[i].test(col))
					continue;
				for(int j = i; j < col; ++j)
					if(mat[i].test(j)) {
						rep[j >> 1] |= 1 << (j & 1);
						break;
					}
			}
			static char buf[maxn];
			for(int i = 0; i < n; ++i)
				buf[i] = rep[i] ? pat[rep[i]] : '.';
			buf[n] = '\0';
			puts(buf);
		}
	}
	return 0;
}