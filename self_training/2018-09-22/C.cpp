#include <bits/stdc++.h>
using namespace std;
const int maxn = 4, maxs = 13, perm[maxs] = {9, 1, 2, 3, 4, 5, 6, 7, 8, 0, 10, 12, 11};
const char *pat[maxs] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
bool read(int cnt[]) {
	for(int i = 0; i < maxs; ++i) {
		static char buf[3];
		if(scanf("%s", buf) != 1)
			return 0;
		for(int j = 0; j < maxs; ++j)
			if(!strcmp(buf, pat[j]))
				++cnt[j];
	}
	return 1;
}
int getNum(int cnt[]) {
	int ret = 0;
	for(int i = 0; i < maxs; ++i)
		ret += cnt[i];
	return ret;
}
int cnt[maxn + 1][maxs];
void getStatement(int id, int rnk, int &val, int &ctr, int &adt) {
	adt = -1;
	switch(id) {
		case 0: {
			if(cnt[id][rnk]) {
				val = rnk;
				ctr = 1;
			} else {
				for(int i = 0; i < maxs; ++i)
					if(cnt[id][perm[i]]) {
						val = perm[i];
						ctr = 1;
						break;
					}
			}
			break;
		}
		case 1 : {
			if(cnt[id][rnk]) {
				val = rnk;
				ctr = cnt[id][rnk];
			} else {
				for(int i = 0; i < maxs; ++i)
					if(cnt[id][perm[i]]) {
						val = perm[i];
						ctr = 1;
						break;
					}
			}
			break;
		}
		case 2 : {
			if(cnt[id][rnk]) {
				val = rnk;
				ctr = cnt[id][rnk];
			} else {
				ctr = maxn + 1;
				for(int i = 0; i < maxs; ++i)
					if(cnt[id][perm[i]] && cnt[id][perm[i]] < ctr) {
						val = perm[i];
						ctr = cnt[id][perm[i]];
					}
			}
			break;
		}
		case 3 : {
			if(cnt[id][rnk] == 3 || cnt[id][rnk] == 4) {
				val = rnk;
				ctr = cnt[id][rnk];
			} else {
				val = rnk;
				ctr = cnt[id][rnk];
				for(int i = 0; i < maxs; ++i)
					if(cnt[id][perm[i]] && perm[i] != val) {
						adt = perm[i];
						break;
					}
			}
			break;
		}
	}
}
bool getChallenge(int id, int pid, int rnk, int ctr) {
	switch(id) {
		case 0 : {
			if((pid + 1) % maxn == id && !cnt[id][(rnk + 1) % maxs])
				return 1;
			if(cnt[id][rnk] + ctr > maxn)
				return 1;
			break;
		}
		case 1 : {
			if((pid + 1) % maxn == id && !cnt[id][(rnk + 1) % maxs])
				return 1;
			break;
		}
		case 2 : {
			if(cnt[id][rnk] == maxn)
				return 1;
			break;
		}
		case 3 : {
			if(!getNum(cnt[pid]))
				return 1;
			break;
		}
	}
	return 0;
}
int main() {
	while(read(cnt[0]) && read(cnt[1]) && read(cnt[2]) && read(cnt[3])) {
		for(int i = 0, j = 0; ; i = (i + 1) % maxn, j = (j + 1) % maxs) {
			int val, ctr, adt;
			getStatement(i, j, val, ctr, adt);
			cnt[i][val] -= ctr;
			cnt[maxn][val] += ctr;
			if(adt != -1) {
				--cnt[i][adt];
				++cnt[maxn][adt];
			}
			for(int k = 1; k < maxn; ++k) {
				int x = (i + k) % maxn;
				if(getChallenge(x, i, j, ctr + (adt != -1))) {
					if(val == j && adt == -1) {
						for(int y = 0; y < maxs; ++y) {
							cnt[x][y] += cnt[maxn][y];
							cnt[maxn][y] = 0;
						}
					} else {
						for(int y = 0; y < maxs; ++y) {
							cnt[i][y] += cnt[maxn][y];
							cnt[maxn][y] = 0;
						}
					}
					break;
				}
			}
			if(!getNum(cnt[i]))
				break;
		}
		for(int i = 0; i < maxn; ++i)
			if(!getNum(cnt[i])) {
				puts("WINNER");
			} else {
				for(int j = 0, k = 0; j < maxs; ++j)
					while(cnt[i][j]--) {
						if(k) {
							putchar(' ');
						} else {
							k = 1;
						}
						printf("%s", pat[j]);
					}
				putchar('\n');
			}
		memset(cnt, 0, sizeof cnt);
	}
	return 0;
}
