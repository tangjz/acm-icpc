#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<long long, int> Node;
const int maxm = 101, maxs = 21;
const char *pat = ".,:;?!*#";
int tot;
map<string, int> Hash;
int getID(char str[]) {
	int i;
	static char buf[maxs];
	for(i = 0; str[i]; ++i)
		buf[i] = str[i] >= 'a' && str[i] <= 'z' ? str[i] : str[i] - 'A' + 'a';
	buf[i] = '\0';
	return Hash.count(buf) ? Hash[buf] : Hash[buf] = ++tot;
}
set<Node> sp;
int n, m, seq[maxm];
char buf[maxs], str[maxm][maxs];
bool vis;
void dfs(int dep, int low, Node cur) {
	if(dep == n)
		return;
	for(int i = low; i < m; ++i) {
		Node nxt = dep < 4 ? make_pair(cur.first << 16 | seq[i], cur.second) : make_pair(cur.first, cur.second << 16 | seq[i]);
		if(!sp.count(nxt)) {
			vis = 1;
			sp.insert(nxt);
		}
		dfs(dep + 1, i + 1, nxt);
	}
}
bool insert() {
	vis = 0;
	dfs(0, 0, make_pair(0LL, 0));
	return vis;
}
int main() {
	for(int Case = 1; scanf("%d", &n) == 1; ++Case) {
		tot = 0;
		map<string, int>().swap(Hash);
		set<Node>().swap(sp);
		sp.insert(make_pair((LL)getID("Joe"), 0));
		while(scanf("%s", buf) == 1) {
			if(buf[1] == '\0') {
				int pos;
				for(pos = 0; buf[0] != pat[pos]; ++pos);
				if(pos < 8) { // end of sentence
					insert();
					m = 0;
					if(pos < 6)
						continue;
					break;
				}
			}
			seq[m] = getID(buf);
			strcpy(str[m++], buf);
		}
		if(Case > 1)
			printf("\n");
		printf("Learning case %d\n", Case);
		while(scanf("%s", buf) == 1) {
			if(buf[1] == '\0') {
				int pos;
				for(pos = 0; buf[0] != pat[pos]; ++pos);
				if(pos < 8) { // end of sentence
					for(int i = 0; i < m; ++i) {
						Node cur = make_pair((LL)seq[i], 0);
						if(!sp.count(cur)) {
							printf("What does the word \"%s\" mean?\n", str[i]);
							sp.insert(cur);
						}
					}
					if(insert()) {
						printf("What does the sentence \"%s", str[0]);
						for(int i = 1; i < m; ++i)
							printf(" %s", str[i]);
						printf("\" mean?\n");
					}
					m = 0;
					if(pos < 6)
						continue;
					break;
				}
			}
			seq[m] = getID(buf);
			strcpy(str[m++], buf);
		}
	}
	return 0;
}
