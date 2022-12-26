#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxm = 31;
int n, m, diff;
char s[maxn], t[maxn];
struct Operation {
	int typ, v0, v1, v2;
	void read() {
		static char op[9];
		scanf("%s", op);
		switch(op[0]) {
			case 'E' : {
				typ = 5;
				break;
			}
			case 'O' : {
				typ = 4;
				break;
			}
			case 'M' : {
				typ = 3;
				break;
			}
			case 'S' : {
				switch(op[1]) {
					case 'H' : {
						typ = 2;
						break;
					}
					case 'E' : {
						typ = 1;
						break;
					}
				}
				break;
			}
		}
		if(typ <= 3)
			scanf("%d%d", &v0, &v1);
		else if(typ == 4)
			scanf("%d%d%d", &v0, &v1, &v2);
	}
} seq[maxm];
void update(char s[], char t[]) {
	int sta = 0;
	for(int i = 1; i <= m; ++i) {
		Operation &cur = seq[i];
		switch(cur.typ) {
			case 1: {
				sta = 0;
				for(int j = 0, k = cur.v0; j < cur.v1; ++j, (++k) == n && (k = 0))
					sta = (sta << 3) + (sta << 1) + (s[k] - '0');
				sta = sta < n ? sta : sta % n;
				break;
			}
			case 2: {
				static char tmp[maxn], tmp2[maxn];
				for(int j = 0, k = sta; j < cur.v0; ++j, (++k) == n && (k = 0))
					tmp[j] = s[k];
				for(int j = 0, k = (cur.v0 + cur.v1) % cur.v0; j < cur.v0; ++j, (++k) == cur.v0 && (k = 0))
					tmp2[k] = tmp[j];
				for(int j = 0, k = sta; j < cur.v0; ++j, (++k) == n && (k = 0)) {
					diff -= s[k] != t[k];
					s[k] = tmp2[j];
					diff += s[k] != t[k];
				}
				break;
			}
			case 3: {
				int rem = 0;
				for(int j = 0, k = (sta + cur.v0 - 1) % n; j < cur.v0; ++j, (--k) < 0 && (k = n - 1)) {
					rem += (s[k] - '0') * cur.v1;
					diff -= s[k] != t[k];
					s[k] = rem % 10 + '0';
					diff += s[k] != t[k];
					rem /= 10;
				}
				break;
			}
			case 4: {
				if(s[cur.v0] == cur.v1 + '0')
					i = cur.v2 - 1;
				break;
			}
			case 5: {
				return;
			}
		}
	}
}
int main() {
	scanf("%d%d%s", &n, &m, s);
	for(int i = 1; i <= m; ++i)
		seq[i].read();
	strcpy(t, s);
	for(int i = 1; ; ++i) {
		update(s, t);
		update(t, s);
		update(t, s);
		if(!diff)
			break;
	}
	for(int i = 1; ; ++i) {
		update(s, t);
		if(!diff) {
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
