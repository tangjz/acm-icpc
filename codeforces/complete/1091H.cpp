#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1;
const char *win = "Alice", *lose = "Bob";
int tot, pr[maxn], d[maxn], sg[maxn];
bitset<maxn> tr;
vector<bitset<maxn> > vis;
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
		if(d[i] == i || i / d[i] == d[i / d[i]])
			tr.set(i);
	}
	tr.reset(m);
	for(int i = 0; i < maxn; ++i) {
		for( ; sg[i] < vis.size() && vis[sg[i]].test(i); ++sg[i]);
		if(sg[i] == vis.size())
			vis.push_back(bitset<maxn>());
		vis[sg[i]] |= tr << i;
	}
	int SG = 0;
	while(n--) {
		int b, w, r;
		scanf("%d%d%d", &b, &w, &r);
		SG ^= sg[w - b - 1] ^ sg[r - w - 1];
	}
	if(!SG)
		swap(win, lose);
	puts(win);
	puts(lose);
	return 0;
}