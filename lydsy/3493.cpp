#include <bits/stdc++.h>
namespace fastIO{
	#define BUF_SIZE 1000001
	bool IOerror = 0;
	inline char next() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) p1 = buf, pend = buf + fread(buf, 1, BUF_SIZE, stdin);
		return *(p1++);
	}
	inline bool blank(char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }
	inline void read(int &x) {
		char ch = next(); x = 0;
		for( ; blank(ch); ch = next());
		for( ; ch >= '0' && ch <= '9'; x = x * 10 + (ch - '0'), ch = next());
	}
	#undef BUF_SIZE
}
typedef long long LL;
const int maxn = (int)1e6 + 1;
const LL INF = ~0U >> 1;
int n, qL, qR, sgn;
LL que[maxn], sum, diff;
inline void upd(LL x) {
	sgn > 0 ? (diff += x) : (diff -= x);
	sgn = -sgn;
}
int main() {
	fastIO::read(n);
	for(int i = 0, x; i < n; ++i) {
		fastIO::read(x);
		if(!x) {
			que[qR++] = INF;
			qL = qR;
		} else {
			sum += x;
			que[qR++] = x;
			while(qL < qR - 2 && que[qR - 3] <= que[qR - 2] && que[qR - 2] >= que[qR - 1]) {
				que[qR - 3] += que[qR - 1] - que[qR - 2];
				qR -= 2;
			}
		}
	}
	for(n = qR; que[qR - 1] != INF; --qR);
	for( ; qR < n && que[qR - 1] >= que[qR]; ++qR);
	qR -= qR < n && (n - qR) & 1;
	for(qL = 0; que[qL] != INF; ++qL);
	for( ; qL > 0 && que[qL - 1] <= que[qL]; --qL);
	qL += qL > 0 && qL & 1;
	std::sort(que + qL, que + qR);
	sgn = 1;
	for(int i = qR - 1; i >= qL; --i)
		if(que[i] != INF)
			upd(que[i]);
	for( ; qL > 0; upd(que[--qL]));
	for( ; qR < n; upd(que[qR++]));
	printf("%lld %lld\n", (sum + diff) / 2, (sum - diff) / 2);
	return 0;
}
