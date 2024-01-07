#include <bits/stdc++.h>
using namespace std;
const int maxn = 128;

int ask(char buf[]) {
	printf("? %s\n", buf);
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	return ret;
}
void close(char buf[]) {
	printf("! %s\n", buf);
	fflush(stdout);
	exit(0);
}

int tot, sum, pL[maxn + 1], pR[maxn + 1];
char buf[maxn + 1], out[maxn + 1];
void solve(int L, int R) { // merge -> [pL[L], pR[L]]
	if(L == R)
		return;
	int M = (L + R) >> 1;
	solve(L, M);
	solve(M + 1, R);
	int lft = pR[L] - pL[L] + 1;
	int rht = pR[M + 1] - pL[M + 1] + 1;
	int pos = 0, i, j;
	static char tmp[maxn + 1];
	for(i = 0, j = 0; i < rht; ++i) {
		for( ; j < lft; ++j) {
			int len = 0;
			for(int k = 0; k < pos; ++k)
				buf[len++] = tmp[k];
			buf[len++] = out[pL[M + 1] + i];
			for(int k = j; k < lft; ++k)
				buf[len++] = out[pL[L] + k];
			buf[len] = '\0';
			int ret = ask(buf);
			if(ret == sum - len)
				break;
			tmp[pos++] = out[pL[L] + j];
		}
		tmp[pos++] = out[pL[M + 1] + i];
	}
	for( ; j < lft; ++j)
		tmp[pos++] = out[pL[L] + j];
	pR[L] = pR[M + 1];
	for(int i = 0; i < pos; ++i)
		out[pL[L] + i] = tmp[i];
}

int main() {
	sum = 0;
	for(char ch = 'a'; sum < maxn && ch <= 'z'; ++ch) {
		for(int i = 0; i < maxn; ++i)
			buf[i] = ch;
		buf[maxn] = '\0';
		int cnt = maxn - ask(buf);
		if(!cnt)
			continue;
		pL[tot] = tot ? pR[tot - 1] + 1 : 0;
		pR[tot] = pL[tot] + cnt - 1;
		for(int i = pL[tot]; i <= pR[tot]; ++i)
			out[i] = ch;
		++tot;
		sum += cnt;
	}
	for(char ch = 'A'; sum < maxn && ch <= 'Z'; ++ch) {
		for(int i = 0; i < maxn; ++i)
			buf[i] = ch;
		buf[maxn] = '\0';
		int cnt = maxn - ask(buf);
		if(!cnt)
			continue;
		pL[tot] = tot ? pR[tot - 1] + 1 : 0;
		pR[tot] = pL[tot] + cnt - 1;
		for(int i = pL[tot]; i <= pR[tot]; ++i)
			out[i] = ch;
		++tot;
		sum += cnt;
	}
	for(char ch = '0'; sum < maxn && ch <= '9'; ++ch) {
		for(int i = 0; i < maxn; ++i)
			buf[i] = ch;
		buf[maxn] = '\0';
		int cnt = maxn - ask(buf);
		if(!cnt)
			continue;
		pL[tot] = tot ? pR[tot - 1] + 1 : 0;
		pR[tot] = pL[tot] + cnt - 1;
		for(int i = pL[tot]; i <= pR[tot]; ++i)
			out[i] = ch;
		++tot;
		sum += cnt;
	}
	solve(0, tot - 1);
	out[sum] = '\0';
	close(out);
	return 0;
}