#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxs = 101, maxl = 6, BASE = (int)1e6, maxn = 17;
const int maxp = 225, maxt = 49, maxc = 1381;
struct BigInt {
	int len, num[maxn];
	BigInt() {
		len = 1;
		num[0] = 0;
	}
	BigInt(int x) {
		len = 0;
		for( ; x > 0; x /= BASE)
			num[len++] = x % BASE;
	}
	BigInt(char buf[]) {
		int blen = strlen(buf);
		len = (blen - 1) / maxl + 1;
		for(int i = 0; i < len; ++i) {
			int R = blen - i * maxl, L = max(R - maxl, 0);
			buf[R] = '\0';
			sscanf(buf + L, "%d", num + i);
		}
	}
	bool operator < (BigInt const &t) const {
		if(len != t.len)
			return len < t.len;
		for(int i = len - 1; i >= 0; --i)
			if(num[i] != t.num[i])
				return num[i] < t.num[i];
		return 0;
	}
	void operator *= (int const &x) {
		int rem = 0;
		for(int i = 0; i < len; ++i) {
			rem += num[i] * x;
			num[i] = rem % BASE;
			rem /= BASE;
		}
		for( ; rem > 0; rem /= BASE)
			num[len++] = rem % BASE;
	}
	void operator /= (int const &x) {
		int rem = 0;
		for(int i = len - 1; i >= 0; --i) {
			rem = rem * BASE + num[i];
			num[i] = rem / x;
			rem %= x;
		}
		for( ; len > 1 && !num[len - 1]; --len);
	}
	void print(char endc = '\n') {
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%0*d", maxl, num[i]);
		if(endc)
			putchar(endc);
	}
} vlim, slim;
int tot, pr[maxp], d[maxp], cnt;
struct Node {
	int ex[maxt];
	BigInt val, sig;
	bool operator < (Node const &t) const {
		return t.val < val;
	}
	void print() {
		val.print(' ');
		sig.print();
	}
} seq[maxc], cur, nxt;
priority_queue<Node> Q;
char buf[maxs];
int main() {
	vlim = 1;
	for(int i = 1; i < maxs; ++i)
		vlim *= 10;
	for(int i = 2; i < maxp; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxp; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	cur.val = cur.sig = 1;
	Q.push(cur);
	int mx = 0;
	while(!Q.empty()) {
		cur = Q.top();
		Q.pop();
		if(vlim < cur.val)
			break;
		if(slim < cur.sig) {
			slim = cur.sig;
			seq[cnt++] = cur;
			for(int i = 0; i < tot; ++i) {
				if(!i || cur.ex[i - 1] > cur.ex[i]) {
					nxt = cur;
					++nxt.ex[i];
					nxt.val *= pr[i];
					nxt.sig /= nxt.ex[i];
					nxt.sig *= nxt.ex[i] + 1;
					Q.push(nxt);
				}
				if(!cur.ex[i])
					break;
				if(mx < i)
					mx = i;
			}
		}
	}
	scanf("%s", buf);
	vlim = buf;
	int L = 0, R = cnt - 1;
	while(L < R) {
		int M = (L + R + 1) >> 1;
		if(vlim < seq[M].val)
			R = M - 1;
		else
			L = M;
	}
	seq[L].val.print();
	return 0;
}
