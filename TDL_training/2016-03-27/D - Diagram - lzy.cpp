#include <cstdio>
#include <set>

using namespace std;

int n, k, d, x[100009];
set<int> s;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i <= n; ++i) scanf("%d", x + i);
	d = x[n] / k;
	for (int i = 0; i < n; ++i) s.insert(x[i]);
	for (int i = 0; i < n; ++i) {
		if (!s.count(x[i])) continue;
		int cnt = 1;
		for (int j = 1; j < k; ++j) {
			set<int>::iterator it = s.find(x[i] + j * d);
			if (it != s.end()) {
				++cnt;
				s.erase(it);
			} else {
				break;
			}
		}
		if (cnt == k) {
			puts("1");
			return 0;
		}
	}
	puts("0");
	return 0;
}
