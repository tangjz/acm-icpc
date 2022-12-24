#include <map>
#include <queue>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <unordered_map>
typedef long long LL;
typedef unsigned int UL;
typedef unsigned long long ULL;
const int maxn = 8, maxl = 4, maxs = 4, maxd = 16;
int tot, idx[33], bits[65537];
struct Country {
	int sum, cnt[5];
	bool operator < (const Country &t) const {
		return sum > t.sum;
	}
} con[33];
std::vector<std::pair<int, int> > trans[257][9];
inline int popcount(UL x) {
	return bits[x >> 16] + bits[x & 65535];
}
int main() {
	for(int i = 1; i < 1 << 16; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	for(int pmsk = 0; pmsk < 1 << 8; ++pmsk)
		for(int cmsk = 0; cmsk < 1 << 8; ++cmsk) {
			if(pmsk & cmsk)
				continue;
			int cnt = 0, dt = 0;
			for(int i = 0; i < 8; ++i)
				if((cmsk >> i) & 1) {
					++cnt;
					i < 4 ? ++dt : --dt;
				}
			trans[pmsk][cnt].push_back(std::make_pair(cmsk, dt));
		}
	int t;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		tot = 0;
		std::map<std::string, int> Hash;
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < 8; ++j) {
				char str[5];
				scanf("%s", str);
				if(!Hash.count(str)) {
					memset(con + tot, 0, sizeof con[0]);
					Hash[str] = tot++;
				}
				++con[Hash[str]].sum;
				++con[Hash[str]].cnt[i];
			}
		std::sort(con, con + tot);
		for(int i = 0, s = 0; i < tot; s += con[i++].sum)
			idx[s] = i;
		std::unordered_map<UL, LL> F;
		std::queue<UL> Q;
		F[0] = 1;
		Q.push(0);
		while(!Q.empty()) {
			static UL pban[5];
			UL pmsk = Q.front(), tmp = pmsk;
			Q.pop();
			int cid = idx[popcount(pmsk)];
			for(int i = 0; i < 4; ++i) {
				pban[i] = tmp & 255;
				tmp >>= 8;
			}
			int dt = 0;
			UL cban0 = 0, ban0 = cban0 | pban[0], cmsk0 = pmsk;
			for(auto it0 : trans[ban0][con[cid].cnt[0]]) {
				int dt0 = dt + it0.second;
				if(dt0 < -1 || dt0 > 1)
					continue;
				UL cban1 = cban0 | it0.first, ban1 = cban1 | pban[1], cmsk1 = cmsk0 | it0.first;
				for(auto it1 : trans[ban1][con[cid].cnt[1]]) {
					int dt1 = dt0 + it1.second;
					if(dt1 < -1 || dt1 > 1)
						continue;
					UL cban2 = cban1 | it1.first, ban2 = cban2 | pban[2], cmsk2 = cmsk1 | it1.first << maxn;
					for(auto it2 : trans[ban2][con[cid].cnt[2]]) {
						int dt2 = dt1 + it2.second;
						if(dt2 < -1 || dt2 > 1)
							continue;
						UL cban3 = cban2 | it2.first, ban3 = cban3 | pban[3], cmsk3 = cmsk2 | it2.first << (maxn << 1);
						for(auto it3 : trans[ban3][con[cid].cnt[3]]) {
							int dt3 = dt2 + it3.second;
							if(dt3 < -1 || dt3 > 1)
								continue;
							UL cmsk = cmsk3 | it3.first << (maxn + (maxn << 1));
							if(cmsk != (~0U) && !F.count(cmsk))
								Q.push(cmsk);
							F[cmsk] += F[pmsk];
						}
					}
				}
			}
		}
		LL sei = 1;
		for(int i = 0; i < tot; ++i)
			for(int j = 0; j < maxl; ++j)
				for(int k = 2; k <= con[i].cnt[j]; ++k)
					sei *= k;
		printf("Case #%d: %lld\n", Case, sei * F[~0U]);
	}
	return 0;
}
