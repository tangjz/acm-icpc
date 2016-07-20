#include <cstdio>
#include <set>

using std::set;

int n, a, l;
set<int> s;

int main() {
	scanf("%d", &n);
	while (n--) {
		scanf("%d", &a);
		s.insert(a);
		for (int i = 2; i * i <= a; ++i) {
			if (a % i == 0) {
				s.insert(i);
				s.insert(a / i);
			}
		}
	}
	l = 1;
	for (auto i: s) {
		if (i - l > 1) break;
		l = i;
	}

	printf("%d\n", ++l);
	return 0;
}
