#include<bits/stdc++.h>
using namespace std;
const int maxn = 100001;
int n, w, h, vc, hc, vid[maxn], hid[maxn], ans[maxn], tmp[maxn];
pair<int, int> pos[maxn], res[maxn];
bool cmp(int const &x, int const &y) {
	return pos[x] < pos[y];
}
int main() {
	scanf("%d%d%d", &n, &w, &h);
	for(int i = 0; i < n; ++i) {
		int typ, x, y;
		scanf("%d%d%d", &typ, &x, &y);
		ans[i] = i;
		pos[i] = make_pair(x - y, y);
		if(typ == 1) {
			res[i] = make_pair(x, h);
			vid[vc] = i;
			++vc;
		} else {
			res[i] = make_pair(w, x);
			hid[hc] = i;
			++hc;
		}
	}
	sort(vid, vid + vc, cmp);
	sort(hid, hid + hc, cmp);
	for(int i = 0, j = 0; i < vc && j < hc; ) {
		int tim = min(pos[vid[i]].first, pos[hid[j]].first), len1 = 0, len2 = 0;
		for( ; i + len1 < vc && pos[vid[i + len1]].first == tim; ++len1)
			tmp[len1] = ans[vid[i + len1]];
		for( ; j + len2 < hc && pos[hid[j + len2]].first == tim; ++len2)
			tmp[len1 + len2] = ans[hid[j + len2]];
		int len = min(len1, len2);
		if(len) {
			rotate(tmp, tmp + (len1 - len), tmp + len1);
			rotate(tmp + len1, tmp + len1 + (len2 - len), tmp + len1 + len2);
			for(int k = 0; k < len; ++k)
				swap(tmp[k], tmp[len1 + k]);
			reverse(tmp, tmp + len);
			reverse(tmp + len1, tmp + len1 + len);
			for(int k = 0; k < len1; ++k)
				ans[vid[i + k]] = tmp[k];
			for(int k = 0; k < len2; ++k)
				ans[hid[j + k]] = tmp[len1 + k];
		}
		i += len1;
		j += len2;
	}
	for(int i = 0; i < n; ++i)
		tmp[ans[i]] = i;
	for(int i = 0; i < n; ++i)
		printf("%d %d\n", res[tmp[i]].first, res[tmp[i]].second);
	return 0;
}