#include <bits/stdc++.h>
using namespace std;
const int maxm = 60, maxh = 24, maxd = 864, maxs = maxd * (maxd + 1) / 2, maxt = maxm * maxh, maxn = 21743 * 6;
int Gcd[maxm + 1][maxm + 1];
inline int gcd(int x, int y) {
	if(x > y)
		swap(x, y);
	while(x && y >= maxm) {
		int r = y % x;
		y = x;
		x = r;
	}
	return x ? Gcd[x][y] : y;
}
int tot;
struct Fraction {
	int num, den;
	Fraction() { num = 0; den = 1; }
	Fraction(int x, int y) {
		assert(x >= 0 && y > 0);
		int r = gcd(x, y);
		num = x / r;
		den = y / r;
	}
	Fraction operator + (Fraction const &t) const {
		int r = gcd(den, t.den);
		return Fraction((num * t.den + den * t.num) / r, den * t.den / r);
	}
	Fraction operator - (Fraction const &t) const {
		int r = gcd(den, t.den);
		return Fraction((num * t.den - den * t.num) / r, den * t.den / r);
	}
	int compare(Fraction const &t) const {
		return num * t.den - den * t.num;
	}
	bool operator < (Fraction const &t) const {
		return compare(t) < 0;
	}
} frac[maxd + 1];
vector<int> vals[maxd + 1];
int cntL, cntR;
struct Info {
	Fraction val;
	int u, v;
	bool operator < (Info const &t) const {
		int dif = val.compare(t.val);
		return dif ? dif < 0 : (u != t.u ? u < t.u : v < t.v);
	}
} lft[maxs + 1], rht[maxs + 1];
int tim, vis[maxt + 1];
vector<int> cand[maxt + 1];
int cntA;
struct Node {
	int x, y, z;
	bool operator < (Node const &t) const {
		return x != t.x ? x < t.x : (y != t.y ? y < t.y : z < t.z);
	}
} ans[maxn + 1];
int main() {
	for(int i = 0; i < maxm; ++i)
		Gcd[0][i] = i;
	for(int i = 1; i < maxm; ++i)
		for(int j = 0; j < maxm; ++j)
			Gcd[i][j] = i > j ? Gcd[j][i] : Gcd[i][j - i];
	set<Fraction> Hash;
	for(int i = 0; i < maxh; ++i)
		for(int j = 1; j < maxm; ++j)
			Hash.insert(Fraction(i, j));
	for(set<Fraction>::const_iterator it = Hash.begin(); it != Hash.end(); ++it) {
		frac[tot] = *it;
		for(int i = 0, j = 0; (i += frac[tot].num) < maxh && (j += frac[tot].den) < maxm; )
			vals[tot].push_back(i * maxm + j);
		++tot;
	}
	for(int i = 0; i < tot; ++i)
		for(int j = i; j < tot; ++j) {
			lft[cntL++] = (Info){frac[i] + frac[j], j, i};
			rht[cntR++] = (Info){frac[j] - frac[i], i, j};
		}
	sort(lft, lft + cntL);
	sort(rht, rht + cntR);
	for(int i = 0, j = 0; i < cntL; ++i) {
		int &a = lft[i].v, &b = lft[i].u, dif;
		for( ; j < cntR && ((dif = rht[j].val.compare(lft[i].val)) < 0 || (!dif && rht[j].u < b)); ++j);
		if(j == cntR)
			break;
		if(dif > 0)
			continue;
		for(vector<int>::const_iterator it = vals[b].begin(); it != vals[b].end(); ++it)
			for(vector<int>::const_iterator jt = vals[a].begin(); jt != vals[a].end(); ++jt) {
				if(a == b && *it < *jt)
					break;
				int pos = *it + *jt;
				if(pos >= maxt)
					continue;
				if(vis[pos] != tim) {
					vis[pos] = tim;
					vector<int>().swap(cand[pos]);
				}
				cand[pos].push_back(*it);
			}
		for(int k = j; k < cntR && !rht[k].val.compare(lft[i].val); ++k) {
			int &c = rht[k].u, &d = rht[k].v;
			for(vector<int>::const_reverse_iterator it = vals[c].rbegin(); it != vals[c].rend(); ++it)
				for(vector<int>::const_reverse_iterator jt = vals[d].rbegin(); jt != vals[d].rend(); ++jt) {
					dif = *jt - *it;
					if(dif < 0)
						break;
					if(vis[dif] != tim)
						continue;
					for(vector<int>::const_iterator kt = cand[dif].begin(); kt != cand[dif].end(); ++kt) {
						if(b == c && *it < *kt)
							break;
						ans[cntA++] = (Node){dif - *kt, *kt, *it};
					}
				}
		}
		++tim;
	}
	for(int i = 0, upp = cntA; i < upp; ++i) {
		int &x = ans[i].x, &y = ans[i].y, &z = ans[i].z;
		if(x == y && y == z) {
			continue;
		} else if(x == y) {
			ans[cntA++] = (Node){x, z, y};
			ans[cntA++] = (Node){z, x, y};
		} else if(y == z) {
			ans[cntA++] = (Node){y, x, z};
			ans[cntA++] = (Node){y, z, x};
		} else if(x == z) {
			ans[cntA++] = (Node){x, z, y};
			ans[cntA++] = (Node){y, x, z};
		} else {
			ans[cntA++] = (Node){x, z, y};
			ans[cntA++] = (Node){y, x, z};
			ans[cntA++] = (Node){y, z, x};
			ans[cntA++] = (Node){z, x, y};
			ans[cntA++] = (Node){z, y, x};
		}
	}
	sort(ans, ans + cntA);
	for(int i = 0; i + 1 < cntA; ++i)
		assert(!(ans[i].x == ans[i + 1].x && ans[i].y == ans[i + 1].y && ans[i].z == ans[i + 1].z));
	int k;
	scanf("%d", &k);
	if(k <= cntA) {
		int &x = ans[k - 1].x, &y = ans[k - 1].y, &z = ans[k - 1].z;
		printf("%02d:%02d %02d:%02d %02d:%02d\n", x / maxm, x % maxm, y / maxm, y % maxm, z / maxm, z % maxm);
	} else {
		puts("-1");
	}
	return 0;
}