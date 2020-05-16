#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e5 + 1, maxn2 = maxn << 1 | 1;
int n, m, a[maxn2], dsu[maxn2];
bool vis[maxn + 2];
int dsuFind(int x) {
	return x == dsu[x] ? x : (dsu[x] = dsuFind(dsu[x]));
}
bool solve(int L, int R) {
	int tot = 0;
	static int seq[maxn2];
	for(int x = L; x <= R; x = dsuFind(x + 1)) {
		seq[++tot] = x;
		while(tot >= 3) {
			int ctr = (a[seq[tot - 2]] > 0) + (a[seq[tot - 1]] > 0) + (a[seq[tot]] > 0);
			if(ctr == 2) {
				if(!a[seq[tot - 2]]) {
					a[seq[tot - 2]] = a[seq[tot]];
					++ctr;
				} else if(!a[seq[tot]]) {
					a[seq[tot]] = a[seq[tot - 2]];
					++ctr;
				}
			}
			if(ctr != 3 || a[seq[tot - 2]] != a[seq[tot]])
				break;
			seq[tot - 2] = seq[tot];
			tot -= 2;
		}
		if(x < R)
			dsu[x] = dsuFind(x + 1);
	}
	for(int i = 1; i < tot; ++i)
		if(a[seq[i]] && a[seq[i + 1]])
			return 0;
	int rt = a[seq[1]], pL = 2, pR = tot - 1;
	while(pL < pR) {
		int lft = a[seq[pL]], rht = a[seq[pR]];
		if(!lft && !rht) {
			for( ; vis[m]; ++m);
			if(m > n)
				return 0;
			vis[m] = 1;
			a[seq[pL++]] = m;
			a[seq[pR--]] = m;
			rt = m;
		} else if(lft) {
			a[seq[++pL]] = rt;
			++pL;
		} else {
			a[seq[--pR]] = rt;
			--pR;
		}
	}
	if(pL == pR && !a[seq[pL]]) {
		for( ; vis[m]; ++m);
		if(m > n)
			return 0;
		vis[m] = 1;
		a[seq[pL]] = m;
	}
	return 1;
}
bool solve() {
	for(int i = 1; i < n + n; ++i) {
		vis[a[i]] = 1;
		dsu[i] = i;
	}
	dsu[n + n] = n + n;
	if(a[1] && a[n + n - 1]) {
		if(a[1] != a[n + n - 1])
			return 0;
	} else if(a[1]) {
		a[n + n - 1] = a[1];
	} else if(a[n + n - 1]) {
		a[1] = a[n + n - 1];
	}
	int tot = 0;
	static int pre[maxn], stk[maxn];
	memset(pre + 1, 0, n * sizeof(int));
	for(int i = 1; i < n + n; ++i) {
		if(!a[i])
			continue;
		if(!pre[a[i]]) {
			stk[++tot] = i;
			pre[a[i]] = i;
			continue;
		}
		for( ; tot && stk[tot] > pre[a[i]]; --tot);
		if(!tot || stk[tot] != pre[a[i]] || (i - pre[a[i]]) & 1 || !solve(pre[a[i]], i))
			return 0;
		stk[tot] = pre[a[i]] = i;
	}
	if(a[1])
		return 1;
	for( ; vis[m]; ++m);
	if(m <= n) {
		a[1] = a[n + n - 1] = m;
		vis[m] = 1;
	} else {
		int tot = 0, spL = 0, spR = 0;
		for(int i = 1; i < n + n; i = dsuFind(i + 1), ++tot)
			spR += a[i] > 0;
		for(int i = 1, j = 1; i < n + n; i = dsuFind(i + 1), ++j) {
			if(!a[i])
				continue;
			--spR;
			if(i & 1 && j > spL + spL && tot - j >= spR + spR) {
				a[1] = a[n + n - 1] = a[i];
				break;
			}
			++spL;
		}
	}
	for(int i = dsuFind(2), j = 1; i < n + n; i = dsuFind(i + 1)) {
		if(a[i] != a[j])
			continue;
		if((i - j) & 1 || !solve(j, i))
			return 0;
		j = i;
	}
	return 1;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n + n; ++i)
		scanf("%d", a + i);
	if(solve()) {
		puts("yes");
		for(int i = 1; i < n + n; ++i)
			printf("%d%c", a[i], " \n"[i == n + n - 1]);
	} else {
		puts("no");
	}
	return 0;
}
