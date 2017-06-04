#include <stdio.h>
const int maxn = 200001;
int row, col, n;
void radix_sort(int len, int seq[], int mx)
{
	static int cnt[maxn];
	for(int i = 0; i <= mx; ++i)
		cnt[i] = 0;
	for(int i = 0; i < len; ++i)
		++cnt[seq[i]];
	len = 0;
	for(int i = 0; i <= mx; ++i)
		if(cnt[i])
			seq[len++] = i;
}
struct Node {
	int tot, seq[maxn], mx;
	int L[maxn], R[maxn];
	void upd(int &x, int y) {
		(x < y) && (x = y);
	}
	void append(int x) {
		seq[tot++] = x;
	}
	void construct() {
		mx = 0;
		radix_sort(tot, seq, seq[1]);
		for(int i = 1; i < tot; ++i) {
			L[seq[i]] = seq[i - 1];
			R[seq[i - 1]] = seq[i];
			upd(mx, seq[i] - seq[i - 1]);
		}
	}
	void erase(int x) {
		L[R[x]] = L[x];
		R[L[x]] = R[x];
		upd(mx, R[x] - L[x]);
	}
} rs, cs;
struct Query {
	char op[2];
	int pos;
	long long ans;
	void parse() {
		scanf("%s%d", op, &pos);
		(op[0] == 'V' ? rs : cs).append(pos);
	}
	void query() {
		ans = (long long)rs.mx * cs.mx;
		(op[0] == 'V' ? rs : cs).erase(pos);
	}
} que[maxn];
int main()
{
	scanf("%d%d%d", &row, &col, &n);
	rs.append(0);
	rs.append(row);
	cs.append(0);
	cs.append(col);
	for(int i = 0; i < n; ++i)
		que[i].parse();
	rs.construct();
	cs.construct();
	for(int i = n - 1; i >= 0; --i)
		que[i].query();
	for(int i = 0; i < n; ++i)
		printf("%lld\n", que[i].ans);
	return 0;
}
