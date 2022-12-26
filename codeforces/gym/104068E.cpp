#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e5 + 1;

void solve() {
	int n, m, typ = -1;
	pair<int, int> card[3];
	static unordered_set<int> ctr[2];
	scanf("%d%d", &n, &m);
	ctr[0].clear();
	ctr[1].clear();
	for(int i = 0; i < 3; ++i) {
		scanf("%d%d", &card[i].first, &card[i].second);
		ctr[0].insert(card[i].first);
		ctr[1].insert(card[i].second);
	}
	sort(card, card + 3);
	reverse(card, card + 3);

	auto binom = [&](LL n, LL m) -> LL {
		if(m < 0 || m > n)
			return 0;
		if(!m)
			return 1;
		if(m == 1)
			return n;
		if(m == 2)
			return n * (n - 1LL) / 2;
		if(m == 3)
			return n * (n - 1LL) * (n - 2) / 6;
		assert(0);
		return -1;
	};

	int aL = ctr[0].size(), bL = ctr[1].size(), aD = card[0].first - card[2].first;
	LL n3 = binom(n, 3), m3 = binom(m, 3), nm3 = binom(n * m, 3);

	LL v0 = 0, v1 = 0, v2 = 0, v3 = 0;
	for(int i = 0, las = n + 1; i < 3; ++i) {
		v0 += binom(min(las, card[i].first) - 1, 3 - i);
		// for(int j = min(las, card[i].first) - 1; j > 0; --j)
		// 	v0 += binom(j - 1, 2 - i);
		if(las <= card[i].first)
			break;
		las = card[i].first;
	}
	for(int i = 0, las = n + 1; i < 3; ++i) {
		if(i != 1) {
			v1 += binom(min(las, card[i].first) - 1, 3 - i - (i == 0));
			// for(int j = min(las, card[i].first) - 1; j > 0; --j)
			// 	v1 += binom(j - 1, 2 - i - (i == 0));
		}
		if((i != 1 && las <= card[i].first) || (i == 1 && las != card[i].first))
			break;
		las = card[i].first;
	}
	for(int i = 0, las = n + 1; i < 3; ++i) {
		if(i != 2) {
			v2 += binom(min(las, card[i].first) - 1, 3 - i - (i <= 1));
			// for(int j = min(las, card[i].first) - 1; j > 0; --j)
			// 	v2 += binom(j - 1, 2 - i - (i <= 1));
		}
		if((i != 2 && las <= card[i].first) || (i == 2 && las != card[i].first))
			break;
		las = card[i].first;
	}
	v3 = card[0].first - 1;

	LL v4 = card[0].first < 3 ? 0 : card[0].first - 3 + (card[1].first > card[0].first - 1 || card[1].first == card[0].first - 1 && card[2].first > card[0].first - 2);
	LL ways = v0;
	LL ways2 = v0 * m * m * m + (v1 + v2) * m * binom(m, 2) + v3 * binom(m, 3);
	LL f[2][6] = {}, ans = 0;

// len(set(a1,a2,a3))=1 三连 #0
	f[0][0] = m3 * n;
		f[1][0] = m3 * v3;
	if(typ != -1) {
		ans += f[0][0];
	} else {
		if(aL == 1) {
			typ = 0;
			ans += f[1][0];
		}
	}

// len(set(b1,b2,b3))=1 len(set(a1,a2,a3))=3 diff(a1,a2,a3)=2 同花顺 #1
	f[0][1] = m * (n - 2LL);
		f[1][1] = m * v4;
	if(typ != -1) {
		ans += f[0][1];
	} else {
		if(aL == 3 && bL == 1 && aD == 2) {
			typ = 1;
			ans += f[1][1];
		}
	}
// len(set(b1,b2,b3))=1 len(set(a1,a2,a3))=3 同花顺、同花 #2
	f[0][2] = n3 * m;
	f[0][2] -= f[0][1];
		f[1][2] = ways * m;
		f[1][2] -= f[1][1];
	if(typ != -1) {
		ans += f[0][2];
	} else {
		if(aL == 3 && bL == 1) {
			typ = 2;
			ans += f[1][2];
		}
	}
// len(set(a1,a2,a3))=3 diff(a1,a2,a3)=2 顺子、同花顺 #3
	f[0][3] = (n - 2LL) * m * m * m;
	f[0][3] -= f[0][1];
		f[1][3] = v4 * m * m * m;
		f[1][3] -= f[1][1];
	if(typ != -1) {
		ans += f[0][3];
	} else {
		if(aL == 3 && aD == 2) {
			typ = 3;
			ans += f[1][3];
		}
	}
// len(set(a1,a2,a3))=3 单牌、顺子、同花顺、同花 #4
// all 对子、三连、单牌、顺子、同花顺、同花 #5
	f[0][4] = n3 * m * m * m;
	f[0][4] -= f[0][1] + f[0][2] + f[0][3];
	f[0][5] = nm3;
	f[0][5] -= f[0][0] + f[0][1] + f[0][2] + f[0][3] + f[0][4];
		f[1][4] = ways * m * m * m;
		f[1][4] -= f[1][1] + f[1][2] + f[1][3];
		f[1][5] = ways2;
		f[1][5] -= f[1][0] + f[1][1] + f[1][2] + f[1][3] + f[1][4];
	if(typ != -1) {
		ans += f[0][4] + f[0][5];
	} else {
		if(aL < 3) {
			typ = 4;
			// ans += f[1][5] + f[0][4];
			ways2 = 0;
			int u, v;
			if(card[0].first == card[1].first) {
				u = card[0].first;
				v = card[2].first;
				ways2 = (u - 1LL) * (n - 1) + (v - 1);
			} else {
				u = card[1].first;
				v = card[0].first;
				ways2 = (u - 1LL) * (n - 1) + (v - 2);
			}
			ways2 *= m * binom(m, 2);
			ans += ways2 + f[0][4];
		} else {
			typ = 5;
			ans += f[1][4];
		}
	}
	printf("%lld\n", ans);
	// printf("n:%d m:%d typ:%d v:%lld %lld %lld %lld (%lld %lld)\n", n, m, typ, v0, v1, v2, v3, ways, ways2);
	// swap(f[0][4], f[0][5]);
	// swap(f[1][4], f[1][5]);
	// for(int i = 0; i < 6; ++i)
	// 	printf("%lld %lld\n", f[0][i], f[1][i]);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
