#include <bits/stdc++.h>
using namespace std;
map<int, int> Hash;
int F(int n) {
	if(Hash.count(n))
		return Hash[n];
	int ret = 0;
	for(int i = 1; i <= n; i <<= 1) {
		int lft = n / (i << 1), rht = n % (i << 1);
		ret = max(ret, F(lft) + (rht > i));
	}
	return Hash[n] = ret;
}
int main() {
	int n;
	scanf("%d", &n);
	Hash[0] = 0;
	printf("%d\n", F(n));
	return 0;
}
