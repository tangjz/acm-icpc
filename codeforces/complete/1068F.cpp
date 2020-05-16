#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e4 + 1, dx[] = {-1, -1, 1, 1, -2, -2, 2, 2}, dy[] = {-2, 2, -2, 2, -1, 1, -1, 1};
int n, m, tot;
pair<int, int> seq[maxn];
void check() {
	int ctr = 0;
	queue<pair<int, int> > que;
	map<pair<int, int>, int> cnt;
	for(int i = 0; i < n; ++i) {
		que.push(seq[i]);
		cnt[seq[i]] = 4;
	}
	while(!que.empty()) {
		++ctr;
		pair<int, int> cur = que.front();
		que.pop();
		for(int i = 0; i < 8; ++i) {
			pair<int, int> nxt = make_pair(cur.first + dx[i], cur.second + dy[i]);
			if((++cnt[nxt]) == 4)
				que.push(nxt);
		}
	}
	printf("need = %d, have = %d\n", n * n / 10, ctr);
}
int main() {
	scanf("%d", &n);
	m = (n + n - 1) / 3 + 1;
	for(int i = 0; i < 3 && tot < n; ++i)
		for(int j = 0; j < m && tot < n; ++j)
			if(!((i + j) & 1))
				seq[tot++] = make_pair(i, j);
//	check();
	for(int i = 0; i < n; ++i)
		printf("%d %d\n", seq[i].first, seq[i].second);
	return 0;
}