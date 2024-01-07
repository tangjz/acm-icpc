#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = (int)3e5 + 1, maxd = 26, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);
int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		static int arr[maxn];
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", arr + i);
		int tim = 0, cL = 0, cR = 0, las = 0;
		for(int L = 0, R = n - 1; L <= R; ++tim) {
			int ctr = 0;
			if(tim & 1) {
				for( ; L <= R && ctr <= las; ctr += arr[R--]);
				cR += ctr;
			} else {
				for( ; L <= R && ctr <= las; ctr += arr[L++]);
				cL += ctr;
			}
			las = ctr;
		}
		printf("%d %d %d\n", tim, cL, cR);
	}
	return 0;
}