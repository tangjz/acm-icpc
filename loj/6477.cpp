#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10001, INF = 0x3f3f3f3f;
int n, m, qtot, que[maxn], stot, b[maxn], nxt[maxn];
pair<int, int> a[maxn], seg[maxn];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].first, &a[i].second);
		que[qtot++] = a[i].second;
	}
	sort(a, a + n);
	sort(que, que + qtot);
	qtot = unique(que, que + qtot) - que;
	memcpy(b, que, qtot * sizeof(int));
	int pos, low = qtot, pre = INF, cur = INF;
	for(int i = n - 1; i >= 0; pre = cur) {
		for(pos = a[i].first; low && pos + m <= que[low - 1]; )
			for(--low; nxt[low] < stot && b[low] <= seg[nxt[low]].first; ++nxt[low]);
		for( ; i >= 0 && a[i].first == pos; --i)
			for(int idx = lower_bound(que + low, que + qtot, a[i].second) - que; idx < qtot; ++idx) {
				for(b[idx] -= m; nxt[idx] < stot && b[idx] <= seg[nxt[idx]].first; ++nxt[idx]);
				if(nxt[idx] < stot && b[idx] < seg[nxt[idx]].second)
					b[idx] = seg[nxt[idx]].first;
			}
		for(int j = low; j < qtot; ++j)
			cur = min(cur, b[j]);
		if(cur < pos) {
			puts("no");
			return 0;
		}
		if(cur < pre && cur - m < pos)
			seg[stot++] = make_pair(cur - m, pos);
	}
	puts("yes");
	return 0;
}
