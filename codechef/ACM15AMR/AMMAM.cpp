#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 1003, maxp = 5;
int n, m, v, c, pr[maxp], a[maxn][maxn], U[maxp][maxn][maxn], D[maxp][maxn][maxn], L[maxp][maxn][maxn], R[maxp][maxn][maxn], tot1, tot2;
pair<int, int> seq1[maxp + 2], seq2[maxp + 2], cur[maxp], tmp[maxp + 2];
long long ans;
void solve(int xL, int xR, int yL, int yR) { // [xL, xR] x [yL, yR]
	if(xL > xR || yL > yR)
		return;
	if(xL == xR && yL == yR) {
		ans += a[xL][yL] == (1 << c) - 1;
		return;
	}
	if(xR - xL + 1 < yR - yL + 1) { // yR - yL + 1 >= 2
		int yM = (yL + yR) >> 1;
		solve(xL, xR, yL, yM);
		solve(xL, xR, yM + 1, yR);
		for(int i = xL; i <= xR; ++i) {
			tot1 = tot2 = 0;
			seq1[tot1++] = make_pair(yM, 0);
			seq2[tot2++] = make_pair(yM + 1, 0);
			int lim1 = yL - 1, lim2 = yR + 1;
			for(int j = i; j <= xR; ++j) { // [i, j]
				{ // jump from (j, yM) to (j, yL)
					int sz = 0;
					for(int k = 0; k < c; ++k) {
						int pos = L[k][j][yM];
						if(pos > lim1) {
							cur[sz++] = make_pair(pos, a[j][pos]);
							if(pos - 1 > lim1 && lim1 < L[k][j][pos - 1])
								lim1 = L[k][j][pos - 1];
						}
					}
					sort(cur, cur + sz, greater<pair<int, int> >());
					sz = unique(cur, cur + sz) - cur;
					int tp = 0, val = -1;
					for(int u = 0, v = 0; u < tot1 || v < sz; )
						if(v == sz || (u < tot1 && seq1[u].first > cur[v].first)) {
							if(val == -1) {
								tmp[tp++] = make_pair(seq1[u].first, val = seq1[u].second);
							} else if(!(val & seq1[u].second)) {
								tmp[tp++] = make_pair(seq1[u].first, seq1[u].second);
								val |= seq1[u].second;
							} else {
								if(lim1 < seq1[u].first)
									lim1 = seq1[u].first;
								break;
							}
							++u;
						} else {
							int dt = cur[v].second;
							if(u < tot1 && seq1[u].first == cur[v].first) {
								if(!(dt & seq1[u].second))
									dt |= seq1[u++].second;
								else {
									if(lim1 < cur[v].first)
										lim1 = cur[v].first;
									break;
								}
							}
							if(val == -1) {
								tmp[tp++] = make_pair(cur[v].first, val = dt);
							} else if(!(val & dt)) {
								tmp[tp++] = make_pair(cur[v].first, dt);
								val |= dt;
							} else {
								if(lim1 < cur[v].first)
									lim1 = cur[v].first;
								break;
							}
							++v;
						}
					for( ; tp && tmp[tp - 1].first <= lim1; --tp);
					swap(tot1, tp);
					swap(seq1, tmp);
				}
				{ // jump from (j, yM + 1) to (j, yR)
					int sz = 0;
					for(int k = 0; k < c; ++k) {
						int pos = R[k][j][yM + 1];
						if(pos < lim2) {
							cur[sz++] = make_pair(pos, a[j][pos]);
							if(pos + 1 < lim2 && lim2 > R[k][j][pos + 1])
								lim2 = R[k][j][pos + 1];
						}
					}
					sort(cur, cur + sz);
					sz = unique(cur, cur + sz) - cur;
					int tp = 0, val = -1;
					for(int u = 0, v = 0; u < tot2 || v < sz; )
						if(v == sz || (u < tot2 && seq2[u].first < cur[v].first)) {
							if(val == -1) {
								tmp[tp++] = make_pair(seq2[u].first, val = seq2[u].second);
							} else if(!(val & seq2[u].second)) {
								tmp[tp++] = make_pair(seq2[u].first, seq2[u].second);
								val |= seq2[u].second;
							} else {
								if(lim2 > seq2[u].first)
									lim2 = seq2[u].first;
								break;
							}
							++u;
						} else {
							int dt = cur[v].second;
							if(u < tot2 && seq2[u].first == cur[v].first) {
								if(!(dt & seq2[u].second))
									dt |= seq2[u++].second;
								else {
									if(lim2 > cur[v].first)
										lim2 = cur[v].first;
									break;
								}
							}
							if(val == -1) {
								tmp[tp++] = make_pair(cur[v].first, val = dt);
							} else if(!(val & dt)) {
								tmp[tp++] = make_pair(cur[v].first, dt);
								val |= dt;
							} else {
								if(lim2 > cur[v].first)
									lim2 = cur[v].first;
								break;
							}
							++v;
						}
					for( ; tp && tmp[tp - 1].first >= lim2; --tp);
					swap(tot2, tp);
					swap(seq2, tmp);
				}
				{ // merge
					seq1[tot1].first = lim1;
					seq2[tot2].first = lim2;
					int msk = 0;
					for(int i = 0; i < tot1; msk |= seq1[i++].second);
					for(int i = tot1 - 1, j = 0; i >= 0; msk ^= seq1[i--].second) {
						for( ; j < tot2 && !(msk & seq2[j].second); msk |= seq2[j++].second);
						if(j && msk == (1 << c) - 1)
							ans += (seq1[i].first - seq1[i + 1].first) * (seq2[j].first - seq2[j - 1].first);
					}
				}
			}
		}
	} else {
		int xM = (xL + xR) >> 1;
		solve(xL, xM, yL, yR);
		solve(xM + 1, xR, yL, yR);
		for(int i = yL; i <= yR; ++i) {
			tot1 = tot2 = 0;
			seq1[tot1++] = make_pair(xM, 0);
			seq2[tot2++] = make_pair(xM + 1, 0);
			int lim1 = xL - 1, lim2 = xR + 1;
			for(int j = i; j <= yR; ++j) { // [i, j]
				{ // jump from (xM, j) to (xL, j)
					int sz = 0;
					for(int k = 0; k < c; ++k) {
						int pos = U[k][xM][j];
						if(pos > lim1) {
							cur[sz++] = make_pair(pos, a[pos][j]);
							if(pos - 1 > lim1 && lim1 < U[k][pos - 1][j])
								lim1 = U[k][pos - 1][j];
						}
					}
					sort(cur, cur + sz, greater<pair<int, int> >());
					sz = unique(cur, cur + sz) - cur;
					int tp = 0, val = -1;
					for(int u = 0, v = 0; u < tot1 || v < sz; )
						if(v == sz || (u < tot1 && seq1[u].first > cur[v].first)) {
							if(val == -1) {
								tmp[tp++] = make_pair(seq1[u].first, val = seq1[u].second);
							} else if(!(val & seq1[u].second)) {
								tmp[tp++] = make_pair(seq1[u].first, seq1[u].second);
								val |= seq1[u].second;
							} else {
								if(lim1 < seq1[u].first)
									lim1 = seq1[u].first;
								break;
							}
							++u;
						} else {
							int dt = cur[v].second;
							if(u < tot1 && seq1[u].first == cur[v].first) {
								if(!(dt & seq1[u].second))
									dt |= seq1[u++].second;
								else {
									if(lim1 < cur[v].first)
										lim1 = cur[v].first;
									break;
								}
							}
							if(val == -1) {
								tmp[tp++] = make_pair(cur[v].first, val = dt);
							} else if(!(val & dt)) {
								tmp[tp++] = make_pair(cur[v].first, dt);
								val |= dt;
							} else {
								if(lim1 < cur[v].first)
									lim1 = cur[v].first;
								break;
							}
							++v;
						}
					for( ; tp && tmp[tp - 1].first <= lim1; --tp);
					swap(tot1, tp);
					swap(seq1, tmp);
				}
				{ // jump from (xM + 1, j) to (xR, j)
					int sz = 0;
					for(int k = 0; k < c; ++k) {
						int pos = D[k][xM + 1][j];
						if(pos < lim2) {
							cur[sz++] = make_pair(pos, a[pos][j]);
							if(pos + 1 < lim2 && lim2 > D[k][pos + 1][j])
								lim2 = D[k][pos + 1][j];
						}
					}
					sort(cur, cur + sz);
					sz = unique(cur, cur + sz) - cur;
					int tp = 0, val = -1;
					for(int u = 0, v = 0; u < tot2 || v < sz; )
						if(v == sz || (u < tot2 && seq2[u].first < cur[v].first)) {
							if(val == -1) {
								tmp[tp++] = make_pair(seq2[u].first, val = seq2[u].second);
							} else if(!(val & seq2[u].second)) {
								tmp[tp++] = make_pair(seq2[u].first, seq2[u].second);
								val |= seq2[u].second;
							} else {
								if(lim2 > seq2[u].first)
									lim2 = seq2[u].first;
								break;
							}
							++u;
						} else {
							int dt = cur[v].second;
							if(u < tot2 && seq2[u].first == cur[v].first) {
								if(!(dt & seq2[u].second))
									dt |= seq2[u++].second;
								else {
									if(lim2 > cur[v].first)
										lim2 = cur[v].first;
									break;
								}
							}
							if(val == -1) {
								tmp[tp++] = make_pair(cur[v].first, val = dt);
							} else if(!(val & dt)) {
								tmp[tp++] = make_pair(cur[v].first, dt);
								val |= dt;
							} else {
								if(lim2 > cur[v].first)
									lim2 = cur[v].first;
								break;
							}
							++v;
						}
					for( ; tp && tmp[tp - 1].first >= lim2; --tp);
					swap(tot2, tp);
					swap(seq2, tmp);
				}
				{ // merge
					seq1[tot1].first = lim1;
					seq2[tot2].first = lim2;
					int msk = 0;
					for(int i = 0; i < tot1; msk |= seq1[i++].second);
					for(int i = tot1 - 1, j = 0; i >= 0; msk ^= seq1[i--].second) {
						for( ; j < tot2 && !(msk & seq2[j].second); msk |= seq2[j++].second);
						if(j && msk == (1 << c) - 1)
							ans += (seq1[i].first - seq1[i + 1].first) * (seq2[j].first - seq2[j - 1].first);
					}
				}
			}
		}
	}
}
int main() {
	while(scanf("%d%d%d", &n, &m, &v) == 3) {
		c = 0;
		for(int i = 2; i * i <= v; ++i)
			if(v % i == 0) {
				pr[c++] = i;
				v /= i;
			}
		if(v > 1)
			pr[c++] = v;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j) {
				int x;
				scanf("%d", &x);
				a[i][j] = 0;
				for(int k = 0; k < c; ++k) {
					bool chk = x % pr[k] == 0;
					if(chk) {
						a[i][j] |= 1 << k;
						U[k][i][j] = i;
						L[k][i][j] = j;
					} else {
						U[k][i][j] = i > 0 ? U[k][i - 1][j] : -1;
						L[k][i][j] = j > 0 ? L[k][i][j - 1] : -1;
					}
				}
			}
		for(int i = n - 1; i >= 0; --i)
			for(int j = m - 1; j >= 0; --j)
				for(int k = 0; k < c; ++k)
					if(a[i][j] & (1 << k)) {
						D[k][i][j] = i;
						R[k][i][j] = j;
					} else {
						D[k][i][j] = i + 1 < n ? D[k][i + 1][j] : n;
						R[k][i][j] = j + 1 < m ? R[k][i][j + 1] : m;
					}
		ans = 0;
		solve(0, n - 1, 0, m - 1);
		printf("%lld\n", ans);
	}
	return 0;
}
