#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 101, maxd = 9, maxv = (int)4e7 + 1, maxh = 9, maxe = 13, INF = 0x3f3f3f3f;
const DB eps = 1e-9, bound = 0.1;
/*
int ans[maxd][maxn], fct[maxe], num[maxh];
// integral part
char dep[maxv];
vector<int> iSeq[maxh];
inline void iUpdate(int h, int v) {
	if(v > 0 && v < maxv && dep[v] == -1) {
		iSeq[h].push_back(v);
		dep[v] = h;
	}
}
inline void iSingleExtend(int h) {
	for(int i = 0; i < (int)iSeq[h].size(); ++i) {
		int v = iSeq[h][i];
		if(v < maxe)
			iUpdate(h, fct[v]);
		int vv = (int)ceil(sqrtl(v));
		for( ; vv * vv <= v; ++vv);
		for( ; vv * vv > v; --vv);
		if(vv * vv == v)
			iUpdate(h, vv);
	}
}
inline int iPow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x *= x)
		(k & 1) && (ret *= x);
	return ret;
}
inline void iDoubleExtend(int h, int hL, int hR) {
	for(int i = 0, iLim = (int)iSeq[hL].size(), jLim = (int)iSeq[hR].size(); i < iLim; ++i) {
		int v1 = iSeq[hL][i];
		for(int j = 0; j < jLim; ++j) {
			int v2 = iSeq[hR][j];
			iUpdate(h, v1 + v2);
			iUpdate(h, v1 - v2);
			if((DB)v1 * v2 < INF)
				iUpdate(h, v1 * v2);
			if(v1 % v2 == 0)
				iUpdate(h, v1 / v2);
			if(pow(v1, v2) < INF)
				iUpdate(h, iPow(v1, v2));
		}
	}
}
// floating part
vector<DB> seq[maxh]; // sorted
inline int dcmp(DB v) {
	return (v > eps) - (v < -eps);
}
inline int find(int mx, DB v) {
	for(int h = 0; h < mx; ++h) {
		int pL = 0, pR = (int)seq[h].size();
		while(pL + 1 < pR) {
			int pM = pL + ((pR - pL) >> 1), sgn = dcmp(seq[h][pM] - v);
			if(!sgn)
				return h;
			(sgn < 0 ? pL : pR) = pM;
		}
		for( ; pL <= pR; ++pL)
			if(!dcmp(seq[h][pL] - v))
				return h;
	}
	return -1;
}
inline void update(int h, DB v) {
	if(v > 0 && v < maxv && find(h, v) == -1)
		seq[h].push_back(v);
}
inline void shrink(int h) {
	int tp = 0;
	sort(seq[h].begin(), seq[h].end());
	for(int i = 0, iLim = (int)seq[h].size(); i < iLim; ++i)
		if(!tp || dcmp(seq[h][tp - 1] - seq[h][i]))
			seq[h][tp++] = seq[h][i];
	seq[h].resize(tp);
}
inline void singleExtend(int h) {
	for(int i = 0; i < (int)seq[h].size(); ++i) {
		DB v = seq[h][i];
		int vi = (int)round(v);
		if(!dcmp(v - vi) && vi < maxe && dcmp(v - fct[vi]))
			update(h, fct[vi]);
		DB vv = sqrtl(v);
		if(dcmp(v - vv) && (!dcmp(v - vi) || dcmp(v - bound) < 0))
			update(h, vv);
	}
}
inline void doubleExtend(int h, int hL, int hR) {
	for(int i = 0, iLim = (int)seq[hL].size(), jLim = (int)seq[hR].size(); i < iLim; ++i) {
		DB v1 = seq[hL][i];
		for(int j = 0; j < jLim; ++j) {
			DB v2 = seq[hR][j];
			update(h, v1 + v2);
			update(h, v1 - v2);
			if(v1 * v2 < INF)
				update(h, v1 * v2);
			if(dcmp(v2))
				update(h, v1 / v2);
			if(pow(v1, v2) < INF)
				update(h, pow(v1, v2));
			if(pow(v1, -v2) < INF)
				update(h, pow(v1, -v2));
		}
	}
}
*/
const char *real_ans = "122222222212133322331344431423134423443313443331231331453343133533244313442445431344324433233333333332232432444344454544344244653435442634245524554444544642343442654434544533233543543454353424245544544335644423124423544325544634244644652454552744245444764434664653333653654445554544345634552455653654445654654444454542352642664454654754455564763555663743354543864455554743353363754445564635256644754446653744355664755445554634234443655445244745335454864456563845356654765545554753444652655525554654345333764555553864455654765555664653333443764555654745366644654465443533254423655434544543352543664554554755365644774566554654445344564555333653343433764555654764456653764546553765466454664555253764454453864546543753345532653466642764466654864565563754454343875555554854455643764556643745356524665555543754445443875546454855356644864466763855355755965435654844234533865445554755356354663465552554344644";
int main() {
	/*
	fct[0] = 1;
	for(int i = 1; i < maxe; ++i)
		fct[i] = fct[i - 1] * i;
	for(int d = 0; d < maxd; ++d) {
		memset(dep, -1, sizeof dep);
		for(int h = 0; h < maxh; ++h)
			num[h] = h ? num[h - 1] * 10 + num[0] : d + 1;
		int mx = 0;
		iUpdate(mx, num[mx]);
		iSingleExtend(mx);
		for(++mx; mx < maxh; ++mx) {
			bool chk = 1;
			for(int v = 1; chk && v < maxn; ++v)
				chk &= dep[v] != -1;
			if(chk)
				break;
			iUpdate(mx, num[mx]);
			for(int h = 0; h < mx; ++h)
				iDoubleExtend(mx, h, mx - 1 - h);
			iSingleExtend(mx);
		}
		fprintf(stderr, "integral #%d: %d\n", d + 1, mx);
		for(int v = 1; v < maxn; ++v) {
			assert(dep[v] != -1);
			ans[d][v] = dep[v];
		}
		for(int h = 0; h < mx; ++h)
			vector<int>().swap(iSeq[h]);
		int mx2 = 0;
		update(mx2, num[mx2]);
		singleExtend(mx2);
		for(++mx2; mx2 < mx; ++mx2) {
			bool chk = 1;
			for(int v = 1; chk && v < maxn; ++v)
				chk &= find(mx2, v) != -1;
			if(chk)
				break;
			update(mx2, num[mx2]);
			for(int h = 0; h < mx2; ++h)
				doubleExtend(mx2, h, mx2 - 1 - h);
			singleExtend(mx2);
			shrink(mx2);
		}
		fprintf(stderr, "floating #%d: %d\n", d + 1, mx2);
		for(int v = 1; v < maxn; ++v) {
			int res = find(mx2, v);
			if(res != -1 && res < ans[d][v])
				ans[d][v] = res;
			if(ans[d][v] + '1' != real_ans[(v - 1) * maxd + d]) {
				printf("diff %d %d: %c %c\n", d + 1, v, real_ans[(v - 1) * maxd + d], ans[d][v] + '1');
			}
		}
		for(int h = 0; h < mx2; ++h)
			vector<DB>().swap(seq[h]);
	}
	*/
	int t, d, n;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &d, &n);
		printf("Case #%d: %c\n", Case, real_ans[(n - 1) * maxd + (d - 1)]);
	}
	return 0;
}
