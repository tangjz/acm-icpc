#include <bits/stdc++.h>
using namespace std;
const char *pat = "hpb";
const int pos[] = {1, 1, 0, 2, 0, 0, 1, 0, 1, 0};
int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		scanf("%d", &n);
		printf("%con\n", pat[pos[n % 10]]);
	}
	return 0;
}