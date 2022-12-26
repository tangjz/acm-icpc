#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e6 + 1, BLEN = 4 << 20 | 1;

struct FastInput {
	char *pool, *head, *tail;
	bool eof;

	FastInput() {
		pool = new char[BLEN];
		head = tail = pool;
		eof = 0;
	}
	~FastInput() {
		delete[] pool;
	}
	char nextChar() {
		if(head == tail) {
			head = pool;
			tail = pool + fread(pool, 1, BLEN, stdin);
			if(head == tail) {
				eof = 1;
				return -1;
			}
		}
		return *(head++);
	}
	void read(int &x) {
		x = 0;
		static char ch, sgn;
		while(isspace(ch = nextChar()));
		if(eof) {
			return;
		}
		(sgn = ch == '-') && (ch = nextChar());
		do x = x * 10 + (ch - '0'); while(isdigit(ch = nextChar()));
		sgn && (x = -x);
	}
} in;

void solve() {
	int n, m, x, y, L = 0, R = 0, L2 = 0, R2 = 0;
	static int a[maxn], que[maxn], que2[maxn];
	static double b[maxn];
	// scanf("%d%d%d%d", &n, &m, &x, &y);
	in.read(n);
	in.read(m);
	in.read(x);
	in.read(y);
	for(int i = 0; i < n; ++i) {
		// scanf("%d", a + i);
		in.read(a[i]);
		b[i] = 0;
		if(L < R && i - que[L] >= m)
			++L;
		for( ; L < R && a[que[R - 1]] <= a[i]; --R);
		que[R++] = i;
		if(i >= m - 1) {
			// printf("winA %d for [%d, %d]\n", que[L], i - m + 1, i);
			b[que[L]] += x;
		}
	}
	L = R = 0;
	for(int i = n - 1, j = n - 1; i >= 0; --i) {
		if(L < R && que[L] - i >= m)
			++L;
		for( ; L < R && a[que[R - 1]] >= a[i]; --R);
		que[R++] = i;
		if(L2 < R2 && que2[L2] - i >= m)
			++L2;
		for(j = min(j, i + m - 1); j > que[L]; --j) {
			if(a[j] == a[que[L]])
				continue;
			for( ; L2 < R2 && a[que2[R2 - 1]] >= a[j]; --R2);
			que2[R2++] = j;
		}
		if(i <= n - m) {
			int k = L2 < R2 ? que2[L2] : n;
			if(L + 1 < R && (k == n || a[k] >= a[que[L + 1]]))
				k = que[L + 1];
			if(k == n)
				continue;
			// printf("winB %d for [%d, %d]\n", k, i, i + m - 1);
			b[k] += y;
		}
	}
	int c = 0;
	double avg = 0, var = 0;
	for(int i = 0; i < n; ++i) {
		if(!b[i])
			continue;
		++c;
		b[i] /= n - m + 1;
		avg += b[i];
	}
	avg /= c;
	for(int i = 0; i < n; ++i)
		if(b[i])
			var += (b[i] - avg) * (b[i] - avg);
	var /= c;
	printf("%d %.4f\n", c, var);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
