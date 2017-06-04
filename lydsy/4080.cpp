// #include <ctime>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int maxn = 101, maxt = 1001;
int n, d, x[maxn], y[maxn], ord[maxn];
bitset<maxn> e[maxn], msk, ans;
inline int sqr(int x) {
	return x * x;
}
int main() {
	// srand(time(0));
	while(scanf("%d%d", &n, &d) == 2) {
		for(int i = 0; i < n; ++i) {
			scanf("%d%d", x + i, y + i);
			ord[i] = i;
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				e[i][j] = sqr(x[i] - x[j]) + sqr(y[i] - y[j]) <= sqr(d);
		for(int t = 0; t < maxt; ++t) {
			for(int i = 0; i < n; ++i)
				swap(ord[i], ord[i + rand() % (n - i)]);
			msk = e[ord[0]];
			for(int i = 1; i < n; ++i)
				if(msk[ord[i]])
					msk &= e[ord[i]];
			if(ans.count() < msk.count())
				ans = msk;
		}
		printf("%d\n", (int)ans.count());
		for(int i = 0; i < n; ++i)
			if(ans[i])
				printf("%d ", i + 1);
		puts("");
	}
	return 0;
}
