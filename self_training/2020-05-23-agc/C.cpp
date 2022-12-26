#include <bits/stdc++.h>
using namespace std;
const int maxs = 797161, maxl = (int)2e5 + 1;
int n, tot, out[maxs];
struct TrieNode {
	int idx, tag, ch[3];
} p[maxs];
int main() {
	static char buf[maxl];
	scanf("%d%s", &n, buf);
	++tot;
	int sta = 0, pw = 1;
	for(int i = 0; i < n; ++i, sta += pw, pw *= 3)
		for(int j = 0; j < pw; ++j) {
			TrieNode &cur = p[sta + j];
			for(int k = 0, adt = 0; k < 3; ++k, adt += pw) {
				p[tot].idx = cur.idx + adt;
				cur.ch[k] = tot++;
			}
		}
	auto expand = [&](int rt) {
		TrieNode &cur = p[rt];
		if(cur.tag) {
			swap(cur.ch[1], cur.ch[2]);
			for(int i = 0; i < 3; ++i)
				p[cur.ch[i]].tag ^= 1;
			cur.tag = 0;
		}
	};
	for(int i = 0; buf[i]; ++i) {
		if(buf[i] == 'S') {
			p[0].tag ^= 1;
			continue;
		}
		for(int j = 0, rt = 0; j < n; ++j) {
			expand(rt);
			TrieNode &cur = p[rt];
			rotate(cur.ch, cur.ch + 2, cur.ch + 3);
			rt = cur.ch[0];
		}
	}
	function<void(int, int, int, int)> dfs = [&](int dep, int rt, int pw, int val) {
		TrieNode &cur = p[rt];
		if(dep == n) {
			out[cur.idx] = val;
		} else {
			expand(rt);
			int npw = pw * 3;
			dfs(dep + 1, cur.ch[0], npw, val);
			dfs(dep + 1, cur.ch[1], npw, val += pw);
			dfs(dep + 1, cur.ch[2], npw, val += pw);
		}
	};
	dfs(0, 0, 1, 0);
	for(int i = 0; i < pw; ++i)
		printf("%d%c", out[i], " \n"[i == pw - 1]);
	return 0;
}