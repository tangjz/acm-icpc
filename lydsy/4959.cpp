#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, ord1[maxn], ord2[maxn], ord[maxn], qtot, etot, que[maxn << 1 | 1], cnt[maxn << 1 | 1], bit[maxn << 1 | 1];
pair<int, int> a[maxn], b[maxn];
set<pair<int, int> > sp;
bool cmp1(int const &x, int const &y) {
	return a[x] < a[y];
}
bool cmp2(int const &x, int const &y) {
	return b[x] < b[y];
}
struct Event {
	int typ, x, yL, yH;
	bool operator < (Event const &t) const {
		return x < t.x || (x == t.x && typ > t.typ);
	}
} e[maxn << 1 | 1];
void bit_add(int x, int v) {
	for( ; x <= etot; x += x & -x)
		bit[x] += v;
}
int bit_sum(int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
bool check() {
	qtot = etot = 0;
	for(int i = 1; i <= n; ++i) {
		que[++qtot] = a[i].second;
		que[++qtot] = b[i].second;
	}
	sort(que + 1, que + qtot + 1);
	qtot = unique(que + 1, que + qtot + 1) - que - 1;
	for(int i = 1; i <= n; ++i) {
		int yL = lower_bound(que + 1, que + qtot + 1, a[i].second) - que;
		int yH = lower_bound(que + 1, que + qtot + 1, b[ord[i]].second) - que;
		e[++etot] = (Event){1, a[i].first, yL, yH};
		e[++etot] = (Event){-1, b[ord[i]].first, yL, yH};
	}
	sort(e + 1, e + etot + 1);
	memset(bit + 1, 0, etot * sizeof(int));
	for(int i = 1; i <= etot; ++i)
		if(e[i].typ == -1) {
			--cnt[e[i].yL];
			bit_add(e[i].yL, -1);
			--cnt[e[i].yH];
			bit_add(e[i].yH, 1);
		} else { // e[i].typ == 1
			if(!cnt[e[i].yL] && !cnt[e[i].yH] && bit_sum(e[i].yL - 1) == bit_sum(e[i].yH)) {
				++cnt[e[i].yL];
				bit_add(e[i].yL, 1);
				++cnt[e[i].yH];
				bit_add(e[i].yH, -1);
			} else {
				return 0;
			}
		}
	return 1;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].first, &a[i].second);
		ord1[i] = i;
	}
	sort(ord1 + 1, ord1 + n + 1, cmp1);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &b[i].first, &b[i].second);
		ord2[i] = i;
	}
	sort(ord2 + 1, ord2 + n + 1, cmp2);
	bool flag = 1;
	for(int i = n, j = n; i >= 1; --i) {
		for( ; j >= 1 && a[ord1[i]] <= b[ord2[j]]; --j)
			sp.insert(make_pair(b[ord2[j]].second, ord2[j]));
		set<pair<int, int> >::iterator it = sp.lower_bound(make_pair(a[ord1[i]].second, 0));
		if(it == sp.end()) {
			flag = 0;
			break;
		}
		ord[ord1[i]] = it -> second;
		sp.erase(it);
	}
	if(flag) {
		flag = check();
		if(flag) {
			for(int i = 1; i <= n; ++i) {
				swap(a[i].first, a[i].second);
				swap(b[i].first, b[i].second);
			}
			flag = check();
		}
	}
	if(flag)
		for(int i = 1; i <= n; ++i)
			printf("%d\n", ord[i]);
	else
		puts("syntax error");
	return 0;
}
