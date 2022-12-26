#include <bits/stdc++.h>
using namespace std;
int mat[81], row[9], col[9], blk[9], lbt[1 << 9 | 1];
bool up[9][9], lft[9][9];
void dfs(int dep) {
	if(dep == 81) {
		for(int i = 0; i < 81; ++i)
			printf("%d%c", mat[i] + 1, " \n"[(i + 1) % 9 == 0]);
		exit(0);
	}
	int x = dep / 9, y = dep % 9, z = (x / 3) * 3 + (y / 3);
	int msk = 511 ^ (row[x] | col[y] | blk[z]);
	if(x % 3)
		msk &= up[x][y] ? 511 << (mat[dep - 9] + 1) : (1 << mat[dep - 9]) - 1;
	if(y % 3)
		msk &= lft[x][y] ? 511 << (mat[dep - 1] + 1) : (1 << mat[dep - 1]) - 1;
	while(msk) {
		int v = msk & -msk;
		mat[dep] = lbt[v];
		msk ^= v;
		row[x] ^= v;
		col[y] ^= v;
		blk[z] ^= v;
		//printf("dep %d: %d\n", dep, lbt[v]);
		dfs(dep + 1);
		row[x] ^= v;
		col[y] ^= v;
		blk[z] ^= v;
	}
}
int main() {
	lbt[0] = -1;
	for(int i = 1; i < 1 << 9; ++i)
		lbt[i] = i & 1 ? 0 : (lbt[i >> 1] + 1);
	for(int i = 0, rid = 0; i < 3; ++i, ++rid)
		for(int j = 0; j < 5; ++j)
			if(j & 1) {
				++rid;
				for(int cid = 0; cid < 9; ++cid) {
					char op[3];
					scanf("%s", op);
					up[rid][cid] = op[0] == '^';
				}
			} else {
				for(int cid = 0; cid < 9; ++cid) {
					if(cid % 3 == 0)
						continue;
					char op[3];
					scanf("%s", op);
					lft[rid][cid] = op[0] == '<';
				}
			}
	dfs(0);
	return 0;
}
