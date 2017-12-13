#include <bits/stdc++.h>
using namespace std;
const char *dirs = "NEWS";
const int maxn = 7, maxs = 25, maxt = 385, maxr = 97, dx[] = {-1, 0, 0, 1}, dy[] = {0, 1, -1, 0};
int t, n, m, tot, cX, cY, st, tim[maxt], val[maxr];
pair<int, int> pos[maxs];
char str[maxn][maxn], buf[maxs];
struct Trans {
	int x, y, s, t;
	void init() {
		char ch1, ch2;
		scanf("%d%d %c %c", &x, &y, &ch1, &ch2);
		for(s = 0; dirs[s] != ch1; ++s);
		for(t = 0; dirs[t] != ch2; ++t);
	}
	int idx() const {
		if(x < 0 || x >= n || y < 0 || y >= m)
			return -1;
		return (x * m + y) << 4 | s << 2 | t;
	}
} sta[2], que[maxt];
struct Recv {
	int x, y, p;
	void init() {
		char ch;
		scanf("%d%d %c", &x, &y, &ch);
		for(p = 0; dirs[p] != ch; ++p);
		// min_rep();
	}
	int idx() const {
		return (x * m + y) << 2 | p;
	}
} stp[5];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		tot = 0;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i) {
			scanf("%s", str[i]);
			for(int j = 0; j < m; ++j)
				if(str[i][j] == '.' || (str[i][j] >= 'a' && str[i][j] <= 'z')) {
					pos[tot] = make_pair(i, j);
					buf[tot++] = str[i][j];
				}
		}
		scanf("%d", &cX);
		for(int i = 0; i < cX; ++i)
			sta[i].init();
		scanf("%d", &cY);
		for(int i = 0; i < cY; ++i)
			stp[i].init();
		bool chk = 0;
		memset(tim, 0, sizeof tim);
		memset(val, 0, sizeof val);
		sort(buf, buf + tot);
		do {
			for(int i = 0; i < tot; ++i)
				str[pos[i].first][pos[i].second] = buf[i];
			int L = 0, R = 0, ctr = 0;
			++st;
			for(int i = 0; i < cX; ++i) {
				int id = sta[i].idx();
				if(id >= 0 && tim[id] != st) {
					tim[id] = st;
					que[R++] = sta[i];
				}
			}
			for(int i = 0; i < cY; ++i)
				val[stp[i].idx()] = st;
			while(L < R) {
				Trans cur = que[L++];
				Recv tmp = (Recv){cur.x, cur.y, cur.s};
				int tid = tmp.idx();
				if(val[tid] == st) {
					++ctr;
					val[tid] = 0;
				}
				if(ctr == cY)
					break;
				char state = str[cur.x][cur.y];
				if(state >= 'a' && state <= 'z')
					state = state - 'a' + 'A';
				if(state == '.' || state == '#' || state == 'X') { // straight
					tmp = (Recv){cur.x, cur.y, cur.t};
					tid = tmp.idx();
					if(val[tid] == st) {
						++ctr;
						val[tid] = 0;
					}
					if(ctr == cY)
						break;
					Trans nxt = (Trans){cur.x + dx[cur.t], cur.y + dy[cur.t], 3 - cur.t, 3 - cur.s};
					int id = nxt.idx();
					if(id >= 0 && tim[id] != st) {
						tim[id] = st;
						que[R++] = nxt;
					}
				}
				if(state == 'O' || state == 'X') { // reflect
					Trans nxt = (Trans){cur.x + dx[cur.s], cur.y + dy[cur.s], 3 - cur.s, cur.t};
					int id = nxt.idx();
					if(id >= 0 && tim[id] != st) {
						tim[id] = st;
						que[R++] = nxt;
					}
				}
				if(state == 'M') { // shift
					tmp = (Recv){cur.x, cur.y, 3 - cur.s};
					tid = tmp.idx();
					if(val[tid] == st) {
						++ctr;
						val[tid] = 0;
					}
					if(ctr == cY)
						break;
					Trans nxt = (Trans){cur.x - dx[cur.s], cur.y - dy[cur.s], cur.s, cur.t};
					int id = nxt.idx();
					if(id >= 0 && tim[id] != st) {
						tim[id] = st;
						que[R++] = nxt;
					}
				}
			}
			if(ctr == cY) {
				chk = 1;
				break;
			}
		} while(next_permutation(buf, buf + tot));
		printf("Case #%d:\n", Case);
		if(!chk)
			puts("No solution!");
		else
			for(int i = 0; i < n; ++i)
				puts(str[i]);
	}
	return 0;
}
