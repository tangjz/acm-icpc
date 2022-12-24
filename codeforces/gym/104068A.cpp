#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1, maxp = 5;
const string pat[] = {"kfc", "crazy", "thursday", "vivo", "50"};

void solve() {
	static char buf[maxn];
	scanf("%s", buf);
	string s;
	for(int i = 0; buf[i]; ++i)
		s.push_back(tolower(buf[i]));
	for(int i = 0; i < maxp; ++i)
		if(s.find(pat[i]) == string::npos) {
			puts("No");
			return;
		}
	puts("Yes");
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}