#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100001, INF = 0x3f3f3f3f;
int n, m, sz[2], rht[maxn + 2], tim[maxn + 2], ord[maxn];
LL ans[maxn];
std::set<int> sp;
struct Node {
	int sta, lim, adt;
	void read() {
		scanf("%d%d%d", &sta, &lim, &adt);
	}
} a[maxn];
bool cmp(int const &u, int const &v) {
	return tim[u] < tim[v];
}
struct Event {
	int idx, tim, L, R;
	void read(int id) {
		idx = id;
		scanf("%d%d%d", &tim, &L, &R);
	}
	bool operator < (Event const &t) const {
		return tim < t.tim || (tim == t.tim && L < t.L);
	}
} que[maxn], eve[2][maxn << 1 | 1];
struct Bit {
	LL bit[maxn];
	void upd(int x, LL v) {
		for( ; x <= n; x += x & -x)
			bit[x] += v;
	}
	LL que(int x) {
		LL ret = 0;
		for( ; x > 0; x -= x & -x)
			ret += bit[x];
		return ret;
	}
	LL que(int L, int R) {
		return que(R) - que(L - 1);
	}
} b[2];
void solve(int sz, Event eve[]) {
	int tot = 0;
	for(int i = 1, j; i <= n; ++i) {
		b[0].bit[i] += a[i].sta;
		if(a[i].sta < a[i].lim && a[i].adt) {
			b[1].bit[i] += a[i].adt;
			tim[i] = (a[i].lim - a[i].sta - 1) / a[i].adt + 1;
			ord[++tot] = i;
		}
		if((j = i + (i & -i)) <= n) {
			b[0].bit[j] += b[0].bit[i];
			b[1].bit[j] += b[1].bit[i];
		}
	}
	std::sort(ord + 1, ord + tot + 1, cmp);
	std::sort(eve + 1, eve + sz + 1);
	for(int i = 1, j = 1; i <= sz; ++i) {
		for(int o; j <= tot && tim[o = ord[j]] <= eve[i].tim; ++j) {
			b[0].upd(o, a[o].lim - a[o].sta);
			b[1].upd(o, -a[o].adt);
		}
		ans[eve[i].idx] += b[0].que(eve[i].L, eve[i].R) + eve[i].tim * b[1].que(eve[i].L, eve[i].R);
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		a[i].read();
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i)
		que[i].read(i);
	std::sort(que + 1, que + m + 1);
	rht[0] = n + 1;
	tim[0] = -1;
	sp.insert(0);
	eve[0][0].R = eve[1][0].R = -1;
	for(int i = 1; i <= m; ++i) {
		for(std::set<int>::iterator it = --sp.upper_bound(que[i].L), jt; it != sp.end(); it = jt) {
			jt = it;
			++jt;
			int pL = *it, pR = rht[pL], pT = tim[pL];
			if(pL > que[i].R)
				break;
			int cL = std::max(pL, que[i].L), cR = std::min(pR, que[i].R);
			if(cL > cR)
				continue;
			if(pT < 0) {
				if(eve[0][sz[0]].idx == que[i].idx && eve[0][sz[0]].R == cL - 1) { // tim == tim
					eve[0][sz[0]].R = cR;
				} else {
					eve[0][++sz[0]] = (Event){que[i].idx, que[i].tim, cL, cR};
				}
			} else if(pT < que[i].tim) {
				int dt = que[i].tim - pT;
				if(eve[1][sz[1]].idx == que[i].idx && eve[1][sz[1]].tim == dt && eve[1][sz[1]].R == cL - 1) {
					eve[1][sz[1]].R = cR;
				} else {
					eve[1][++sz[1]] = (Event){que[i].idx, dt, cL, cR};
				}
			}
			if(cR < pR) {
				rht[cR + 1] = pR;
				tim[cR + 1] = pT;
				sp.insert(cR + 1);
				jt = it;
				++jt;
			}
			if(pL < cL) {
				rht[pL] = cL - 1;
			} else {
				sp.erase(pL);
			}
		}
		rht[que[i].L] = que[i].R;
		tim[que[i].L] = que[i].tim;
		sp.insert(que[i].L);
	}
	solve(sz[0], eve[0]);
	for(int i = 1; i <= n; ++i)
		a[i].sta = b[0].bit[i] = b[1].bit[i] = 0;
	solve(sz[1], eve[1]);
	for(int i = 1; i <= m; ++i)
		printf("%I64d\n", ans[i]);
	return 0;
}
