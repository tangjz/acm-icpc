#include <cstdio>
#include <vector>
#include <algorithm>
const char Figure[] = "23456789TJQKA", Suit[] = "CDHS";
int scan(char buf[]) {
	for(int i = 0; Figure[i]; ++i)
		if(buf[0] == Figure[i])
			for(int j = 0; Suit[j]; ++j)
				if(buf[1] == Suit[j])
					return i << 2 | j;
	return -1;
}
int getRoyalFlush(int seq[]) {
	int suit = seq[0] & 3;
	for(int i = 0; i < 5; ++i)
		if((seq[i] >> 2) != i + 8 || (seq[i] & 3) != suit)
			return 0;
	return 1;
}
int getStraightFlush(int seq[]) {
	int figure = seq[0] >> 2, suit = seq[0] & 3;
	for(int i = 1; i < 5; ++i)
		if((seq[i] >> 2) != figure + i || (seq[i] & 3) != suit)
			return i == 4 && (seq[i] >> 2) == figure + 12 && (seq[i] & 3) == suit ? 3 : 0;
	return figure + 4;
}
int getFourOfAKind(int seq[]) {
	if((seq[1] >> 2) != (seq[2] >> 2) || (seq[2] >> 2) != (seq[3] >> 2)) // AAAAB or ABBBB
		return 0;
	if((seq[0] >> 2) == (seq[1] >> 2))
		return (seq[3] >> 2) << 4 | seq[4] >> 2;
	if((seq[3] >> 2) == (seq[4] >> 2))
		return (seq[1] >> 2) << 4 | seq[0] >> 2;
	return 0;
}
int getFullHouse(int seq[]) {
	if((seq[0] >> 2) != (seq[1] >> 2) || (seq[3] >> 2) != (seq[4] >> 2)) // AAABB or AABBB
		return 0;
	if((seq[1] >> 2) == (seq[2] >> 2))
		return (seq[2] >> 2) << 4 | seq[3] >> 2;
	if((seq[2] >> 2) == (seq[3] >> 2))
		return (seq[2] >> 2) << 4 | seq[1] >> 2;
	return 0;
}
int getFlush(int seq[]) {
	int ret = seq[4] >> 2, suit = seq[4] & 3;
	for(int i = 3; i >= 0; --i) {
		if((seq[i] & 3) != suit)
			return 0;
		ret = ret << 4 | seq[i] >> 2;
	}
	return ret;
}
int getStraight(int seq[]) {
	int figure = seq[0] >> 2;
	for(int i = 1; i < 5; ++i)
		if((seq[i] >> 2) != figure + i)
			return i == 4 && (seq[i] >> 2) == figure + 12 ? 3 : 0;
	return figure + 4;
}
int getThreeOfAKind(int seq[], bool hasFive = 1) {
	if(!hasFive)
		return (seq[0] >> 2) == (seq[1] >> 2) && (seq[0] >> 2) == (seq[2] >> 2) ? ((seq[0] >> 2) + 1) << 8 : 0;
	for(int i = 0; i < 3; ++i)
		if((seq[i] >> 2) == (seq[i + 1] >> 2) && (seq[i] >> 2) == (seq[i + 2] >> 2)) {
			int ret = (seq[i] >> 2) + 1;
			if(i < 2)
				ret = ret << 4 | seq[4] >> 2;
			if(i < 1)
				ret = ret << 4 | seq[3] >> 2;
			if(i > 1)
				ret = ret << 4 | seq[1] >> 2;
			if(i > 0)
				ret = ret << 4 | seq[0] >> 2;
			return ret;
		}
	return 0;
}
int getTwoPair(int seq[]) {
	int ret = 0, cnt = 0, val = 0;
	for(int i = 4; i >= 0; --i)
		if(i > 0 && (seq[i] >> 2) == (seq[i - 1] >> 2)) {
			ret = ret << 4 | seq[--i] >> 2;
			++cnt;
		} else {
			val = seq[i] >> 2;
		}
	return cnt == 2 ? ret << 4 | val : 0;
}
int getPair(int seq[], bool hasFive = 1) {
	if(!hasFive) {
		if((seq[1] >> 2) == (seq[2] >> 2))
			return (seq[1] >> 2) << 12 | (seq[0] >> 2) << 8;
		if((seq[0] >> 2) == (seq[1] >> 2))
			return (seq[0] >> 2) << 12 | (seq[2] >> 2) << 8;
		return 0;
	}
	int ret = 0, cnt = 0, val = 0;
	for(int i = 4; i >= 0; --i)
		if(!cnt && i > 0 && (seq[i] >> 2) == (seq[i - 1] >> 2)) {
			val = seq[--i] >> 2;
			++cnt;
		} else {
			ret = ret << 4 | seq[i] >> 2;
		}
	return cnt == 1 ? val << 12 | ret : 0;
}
/*int getHighCard(int seq[], bool hasFive = 1) {
	if(!hasFive)
		return (seq[2] >> 2) << 16 | (seq[1] >> 2) << 12 | (seq[0] >> 2) << 8;
	return (seq[4] >> 2) << 16 | (seq[3] >> 2) << 12 | (seq[2] >> 2) << 8 | (seq[1] >> 2) << 4 | seq[0] >> 2;
}*/
const int maxs = 1 << 14 | 1;
int bits[maxs];
std::vector<int> tr[maxs];
int t, seq[15], sel[5], typ[maxs], val[maxs];
char buf[3];
void dfs(int dep, int low, int msk) {
	if(dep == 3) {
		int tmp = getThreeOfAKind(sel, 0);
		if(tmp) {
			typ[msk] = 3;
			val[msk] = tmp;
		} else {
			tmp = getPair(sel, 0);
			if(tmp) {
				typ[msk] = 1;
				val[msk] = tmp;
			} else {
				typ[msk] = 0;
			}
		}
	}
	if(dep == 5) {
		int tmp = getRoyalFlush(sel);
		if(tmp) {
			typ[msk] = 9;
			val[msk] = tmp;
			return;
		}
		tmp = getStraightFlush(sel);
		if(tmp) {
			typ[msk] = 8;
			val[msk] = tmp;
			return;
		}
		tmp = getFourOfAKind(sel);
		if(tmp) {
			typ[msk] = 7;
			val[msk] = tmp;
			return;
		}
		tmp = getFullHouse(sel);
		if(tmp) {
			typ[msk] = 6;
			val[msk] = tmp;
			return;
		}
		tmp = getFlush(sel);
		if(tmp) {
			typ[msk] = 5;
			val[msk] = tmp;
			return;
		}
		tmp = getStraight(sel);
		if(tmp) {
			typ[msk] = 4;
			val[msk] = tmp;
			return;
		}
		tmp = getThreeOfAKind(sel);
		if(tmp) {
			typ[msk] = 3;
			val[msk] = tmp;
			return;
		}
		tmp = getTwoPair(sel);
		if(tmp) {
			typ[msk] = 2;
			val[msk] = tmp;
			return;
		}
		tmp = getPair(sel);
		if(tmp) {
			typ[msk] = 1;
			val[msk] = tmp;
			return;
		}
		typ[msk] = 0;
		return;
	}
	for(int i = low; i < 14; ++i) {
		sel[dep] = seq[i];
		dfs(dep + 1, i + 1, msk | 1 << i);
	}
}
const int score[2][10] = {{0, 0, 0, 0, 2, 4, 6, 10, 15, 25}, {0, 0, 0, 2, 4, 8, 12, 20, 30, 50}};
bool cmp(int const &u, int const &v) {
	if(typ[u] != typ[v])
		return typ[u] < typ[v];
	return val[u] < val[v];
}
int main() {
	int all = (1 << 14) - 1;
	for(int i = 1; i <= all; ++i) {
		bits[i] = bits[i >> 1] + (i & 1);
		if(bits[i] == 9) {
			tr[all].push_back(i);
			for(int j = (i - 1) & i; j; j = (j - 1) & i)
				if(bits[j] == 4)
					tr[i].push_back(j);
		}
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		for(int i = 0; i < 14; ++i) {
			scanf("%s", buf);
			seq[i] = scan(buf);
		}
		std::sort(seq, seq + 14);
		dfs(0, 0, 0);
		int ans = 0;
		for(auto &it : tr[all]) {
			int msk1 = all - it, sc1 = score[0][typ[msk1]];
			if(sc1 + score[1][typ[msk1]] + 22 <= ans)
				continue;
			for(auto &jt : tr[it]) {
				int msk2 = it - jt, sc2 = sc1 + score[1][typ[msk2]];
				if(cmp(msk1, msk2) || sc2 + 22 <= ans)
					continue;
				for(int tmp = jt, ban = tmp & -tmp; tmp; tmp -= ban, ban = tmp & -tmp) {
					int msk3 = jt - ban, sc3 = sc2;
					if(cmp(msk2, msk3))
						continue;
					if(typ[msk3] == 3)
						sc3 += (val[msk3] >> 8) + 9;
					else if(typ[msk3] == 1)
						sc3 += std::max((val[msk3] >> 12) - 3, 0);
					if(ans < sc3)
						ans = sc3;
				}
			}
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
