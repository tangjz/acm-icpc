#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, a[maxn], c[3];
void update(int x, int d) {
	static map<int, int> ctr;
	int &v = ctr[x];
	--c[min(v, 2)];
	v += d;
	++c[min(v, 2)];
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		update(a[i], 1);
	}
	bool chk = 0;
	for(int i = 0; !chk && i < n; ++i)
		if(a[i]) {
			update(a[i], -1);
			update(a[i] - 1, 1);
			chk |= !c[2];
			update(a[i] - 1, -1);
			update(a[i], 1);
		}
	if(chk) {
		chk = 0;
		for(int i = 0; i < n; ++i)
			chk ^= (a[i] + i) & 1;
	}
	puts(chk ? "sjfnb" : "cslnb");
	return 0;
}