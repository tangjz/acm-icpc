#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000003;
typedef long long LL;
int n, p[maxn];
LL a[maxn], b[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", p + i);
		{ // i + k <= n : k <= n - i
			int L = 0, R = n - i;
			{ // i + k <= p[i] : k <= p[i] - i
				int pL = max(L, 0), pR = min(R, p[i] - i);
				if(pL <= pR) {
					a[pL] += p[i] - i - pL;
					a[pR + 1] -= p[i] - i - pR;
					b[pL + 1] += -1;
					b[pR + 1] -= -1;
				}
			}
			{ // p[i] < i + k : k >= p[i] - i + 1
				int pL = max(L, p[i] - i + 1), pR = min(R, n - 1);
				if(pL <= pR) {
					a[pL] += i + pL - p[i];
					a[pR + 1] -= i + pR - p[i];
					b[pL + 1] += 1;
					b[pR + 1] -= 1;
				}
			}
		}
		{ // i + k > n : k >= n - i + 1
			int L = n - i + 1, R = n - 1;
			{ // i + k - n <= p[i] : k <= n - i + p[i]
				int pL = max(L, 0), pR = min(R, n - i + p[i]);
				if(pL <= pR) {
					a[pL] += p[i] - i - pL + n;
					a[pR + 1] -= p[i] - i - pR + n;
					b[pL + 1] += -1;
					b[pR + 1] -= -1;
				}
			}
			{ // p[i] < i + k - n : k >= n - i + p[i] + 1
				int pL = max(L, n - i + p[i] + 1), pR = min(R, n - 1);
				if(pL <= pR) {
					a[pL] += i + pL - n - p[i];
					a[pR + 1] -= i + pR - n - p[i];
					b[pL + 1] += 1;
					b[pR + 1] -= 1;
				}
			}
		}
	}
	int pos = -1;
	LL ans = ~0ULL >> 1;
	for(int i = 1; i < n; ++i)
		b[i] += b[i - 1];
	for(int i = 0; i < n; ++i) {
		a[i] += b[i] + (i ? a[i - 1] : 0);
		if(a[i] < ans) {
			ans = a[i];
			pos = i;
		}
	}
	printf("%I64d %d\n", ans, pos);
	return 0;
}
