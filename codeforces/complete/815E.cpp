#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
int tot;
LL n, m, len;
map<LL, LL> cnt;
int main() {
	scanf("%I64d%I64d", &n, &m);
	if(m <= 2) {
		printf("%I64d\n", m == 1 ? 1LL : n);
		return 0;
	} // else n >= m > 2
	m -= 2;
	cnt[n - 2] = 1;
	while(1) {
		LL nxt = (cnt.rbegin() -> first - 1) >> 1, ctr = 0;
		while(cnt.size() > 0 && (cnt.rbegin() -> first - 1) >> 1 == nxt) {
			pair<LL, LL> tmp = *cnt.rbegin();
			cnt.erase(tmp.first);
			ctr += tmp.second;
			if(tmp.first >> 1) {
				if((tmp.first - 1) >> 1)
					cnt[(tmp.first - 1) >> 1] += tmp.second;
				cnt[tmp.first >> 1] += tmp.second;
			}
		}
		if(ctr < m) {
			m -= ctr;
		} else {
			len = nxt;
			break;
		}
	}
	LL L = 2, R = n - 1;
	while(len < (R - L) >> 1) {
		LL M = (L + R) >> 1, ctr = 0;
		map<LL, LL>().swap(cnt);
		cnt[(R - L) >> 1] = 1; // [L, M) (M, R]
		while(1) {
			LL nxt = (cnt.rbegin() -> first - 1) >> 1;
			while(cnt.size() > 0 && (cnt.rbegin() -> first - 1) >> 1 == nxt) {
				pair<LL, LL> tmp = *cnt.rbegin();
				cnt.erase(tmp.first);
				if(nxt == len)
					ctr += tmp.second;
				if(tmp.first >> 1) {
					if((tmp.first - 1) >> 1)
						cnt[(tmp.first - 1) >> 1] += tmp.second;
					cnt[tmp.first >> 1] += tmp.second;
				}
			}
			if(nxt <= len)
				break;
		}
		if(ctr < m) {
			m -= ctr;
			L = M + 1;
		} else {
			R = M - 1;
		}
	}
	printf("%I64d\n", (L + R + (m - 1)) >> 1);
	return 0;
}
