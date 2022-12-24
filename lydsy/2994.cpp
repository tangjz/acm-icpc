#include <bits/stdc++.h>
using namespace std;
const int maxn = 301;
string pat, sub[maxn];
int len, num[maxn];
char buf[maxn];
void read() {
	scanf("%s", buf);
	for(len = 0; buf[len]; ++len)
		num[len] = buf[len] - '0';
	reverse(num, num + len);
	pat = "";
	while(len > 0) {
		pat += "01"[num[0] & 1];
		num[0] >>= 1;
		for(int i = 1; i < len; ++i) {
			if(num[i] & 1)
				num[i - 1] += 5;
			num[i] >>= 1;
		}
		if(!num[len - 1])
			--len;
	}
	reverse(pat.begin(), pat.end());
}
void write() {
	len = 1;
	num[0] = 0;
	for(int i = 0; i < (int)pat.length(); ++i) {
		num[0] = num[0] << 1 | (pat[i] == '1');
		for(int j = 1; j < len; ++j) {
			num[j] <<= 1;
			if(num[j - 1] >= 10) {
				num[j - 1] -= 10;
				++num[j];
			}
		}
		if(num[len - 1] >= 10) {
			num[len - 1] -= 10;
			num[len++] = 1;
		}
	}
	for(int i = 0; i < len; ++i)
		buf[i] = '0' + num[len - 1 - i];
	buf[len] = '\0';
	puts(buf);
}
int pL[maxn], pR[maxn];
void pfs(int u) {
	if(pat[u] == '0') {
		sub[u] = "0";
	} else {
		pfs(pL[u] = u + 1);
		pfs(pR[u] = pL[u] + sub[pL[u]].length());
		sub[u] = "1" + sub[pL[u]] + sub[pR[u]];
	}
}
bool vis;
string replicate(string const pat, int k) {
	string ret = "";
	while((k--) > 0)
		ret += pat;
	return ret;
}
void dfs(int u) {
	if(!pL[u])
		return;
	dfs(pR[u]);
	if(!vis && sub[pR[u]].length() > 2) {
		vis = 1;
		sub[pL[u]] = sub[pL[u]].substr(0, sub[pL[u]].length() - 1) + "100";
		sub[pR[u]] = replicate("10", (sub[pR[u]].length() - 3) / 2) + "0";
	}
	if(!vis)
		dfs(pL[u]);
	if(vis)
		sub[u] = "1" + sub[pL[u]] + sub[pR[u]];
}
int main() {
	read();
	pfs(0);
	dfs(0);
	pat = vis ? sub[0] : replicate("10", (sub[0].length() - 1) / 2) + "0";
	write();
	return 0;
}
