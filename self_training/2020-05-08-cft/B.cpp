#include <bits/stdc++.h>
using namespace std;
int main() {
	int t = 1;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		auto check = [&]() {
			if(a != c)
				swap(c, d);
			return a == c && a == b + d;
		};
		bool chk = check();
		if(!chk) {
			swap(a, b);
			chk = check();
		}
		puts(chk ? "Yes" : "No");
	}
	return 0;
}