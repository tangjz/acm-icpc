#include <cctype>
#include <cstdio>
#include <vector>
#include <set>

#define N 200000

using namespace std;

int n, m, a, b, w[N + 9];
set<int> s;
vector<int> r[N + 9];
int d[N + 9];

void get(int &x) {
	x = 0;
	int c;
	while (isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
}

int main() {
	while (scanf("%d%d%*c", &n, &m) == 2) {
		for (int i = 1; i < n; ++i)
			get(w[i]);
		for (int i = 1; i <= n; ++i)
			r[i].clear();
		for (int i = 1; i <= m; ++i) {
			d[i] = 0;
			get(a), get(b);
			if (a > b) swap(a, b);
			r[a].push_back(+i);
			r[b].push_back(-i);
		}
		s.clear();
		for (int i = 1; i < n; ++i) {
			for (int j: r[i])
				if (j > 0) s.insert(+j);
				else s.erase(-j);
			if (!s.empty()) {
				//printf("%d %d %d\n", i, *s.begin(), *s.rbegin());
				d[*s.begin()] += w[i];
				d[*s.rbegin() + 1] -= w[i];
			}
		}
		int sum = 0;
		for (int i = 1; i <= m; ++i) {
			sum += d[i];
			printf("%d\n", sum);
		}
	}
	return 0;
}
