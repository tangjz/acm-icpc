#include <bits/stdc++.h>
using namespace std;
string min_rep(int val) {
	const int maxp = 13, num[maxp] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	const string pat[maxp] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	string ret = "";
	for(int i = 0; i < maxp; ++i)
		for( ; val >= num[i]; ret += pat[i], val -= num[i]);
	return ret;
}
double dfs(string rep, int val) {
	const int maxp = 7, num[maxp] = {1, 5, 10, 50, 100, 500, 1000};
	const char *pat = "IVXLCDM";
	int las = maxp;
	for(int i = 0; i < maxp; ++i)
		if(rep.back() == pat[i])
			las = i;
	int tot = 1;
	double ret = val;
	for(int i = 0; i < maxp; ++i) {
		int nxt = val + num[i];
		if(las < i) {
			if((las & 1) || las + 2 < i)
				continue;
			nxt -= num[las] << 1;
		}
		if(nxt < num[maxp - 1] && min_rep(nxt) == rep + pat[i]) {
			tot += 7;
			ret += 7 * dfs(rep + pat[i], nxt);
		}
	}
	ret /= tot;
	return ret;
}
int main() {
	printf("%.8f\n", dfs("", 0) + 7000 / 43.0);
	return 0;
}
