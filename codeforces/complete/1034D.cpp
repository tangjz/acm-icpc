#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1, maxm = maxn << 2 | 1;
int n, m, etot;
set<pair<pair<int, int>, int> > sp;
struct Event {
	int l, r, v;
} eve[maxm];
LL calc(int low) {
	LL cnt = 0;
	static int dt[maxn];
	memset(dt + 1, 0, n * sizeof(int));
	for(int L = 1, R = 1, i = 0, len = 0; R <= n; ++R) {
		for( ; i < etot && eve[i].r == R; ++i) {
			dt[eve[i].l] += eve[i].v;
			if(L <= eve[i].l)
				len += eve[i].v;
		}
		for( ; L <= R && len >= low; ++L)
			len -= dt[L];
		cnt += L - 1;
	}
	return cnt;
}
LL bit[2][maxn];
void bit_add(LL bit[], int x, LL v) {
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
LL bit_sum(LL bit[], int x) {
	LL ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
void solve(int low) {
	LL cnt = 0, sum = 0;
	static int dt[maxn];
	memset(dt + 1, 0, n * sizeof(int));
	for(int L = 1, R = 1, i = 0, len = 0; R <= n; ++R) {
		for( ; i < etot && eve[i].r == R; ++i) {
			bit_add(bit[0], eve[i].l, eve[i].v);
			bit_add(bit[1], eve[i].l, (LL)eve[i].l * eve[i].v);
			dt[eve[i].l] += eve[i].v;
			if(L <= eve[i].l)
				len += eve[i].v;
		}
		for( ; L <= R && len > low; ++L)
			len -= dt[L];
		cnt += L - 1;
		sum += bit_sum(bit[1], L - 1) + (L - 1) * (bit_sum(bit[0], R) - bit_sum(bit[0], L - 1));
	}
	sum += (m - cnt) * low;
	printf("%I64d\n", sum);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		int pL, pR;
		scanf("%d%d", &pL, &pR);
		eve[etot++] = (Event){i, i, pR - pL}; // [pL, pR)
		if(!sp.empty()) {
			set<pair<pair<int, int>, int> >::iterator it = sp.upper_bound(make_pair(make_pair(pR, pR), 0));
			if(it != sp.begin())
				--it;
			while((it -> first).second > pL) {
				bool chk = it == sp.begin();
				set<pair<pair<int, int>, int> >::iterator jt = it--;
				int qL = (jt -> first).first, qR = (jt -> first).second, qID = jt -> second;
				if(qL < pR) {
					sp.erase(jt);
					if(pL <= qL && qR <= pR) {
						eve[etot++] = (Event){qID, i, -(qR - qL)};
					} else if(qL <= pL && pR <= qR) {
						sp.insert(make_pair(make_pair(qL, pL), qID));
						sp.insert(make_pair(make_pair(pR, qR), qID));
						eve[etot++] = (Event){qID, i, -(pR - pL)};
					} else if(pL <= qL) {
						sp.insert(make_pair(make_pair(pR, qR), qID));
						eve[etot++] = (Event){qID, i, -(pR - qL)};
					} else {
						sp.insert(make_pair(make_pair(qL, pL), qID));
						eve[etot++] = (Event){qID, i, -(qR - pL)};
					}
				}
				if(chk)
					break;
			}
		}
		sp.insert(make_pair(make_pair(pL, pR), i));
	}
	int vL = 1, vR = (int)1e9 - 1;
	while(vL < vR) {
		int vM = (vL + vR + 1) >> 1;
		if(calc(vM) >= m) {
			vL = vM;
		} else {
			vR = vM - 1;
		}
	}
	solve(vL);
	return 0;
}
