#include <cctype>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <bitset>

using namespace std;

#define N 1000
#define L 2000

typedef unsigned long long u64;

int k, n, m, l;
int len[N + 9];
char q[L + 9];
int o[N + 9];
u64 h[N + 9];
bitset<L + 9> d[N + 9], c;

#define MAGIC 23333
u64 Hash(const char s[]) {
	u64 h = 0;
	while (*s) h = h * MAGIC + (tolower(*s++) - 'a');
	return h;
}

//~ bool eql(const char s[], const char t[]) {
	//~ auto n = strlen(s);
	//~ if (n != strlen(t)) return false;
	//~ for (auto i = 0u; i < n; ++i)
		//~ if (tolower(s[i]) != tolower(t[i])) return false;
	//~ return true;
//~ }

bool cmp(int a, int b) {
	return h[a] < h[b];
}

int main() {
	scanf("%d", &k);
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", q);
		len[i] = strlen(q);
		h[i] = Hash(q);
		for (int j = 0; j < len[i]; ++j)
			if (isupper(q[j])) d[i].set(j);
	}
	for (int i = 0; i <= n; ++i) o[i] = i;
	sort(o, o + n, cmp);
	scanf("%d", &m);
	while (m--) {
		scanf("%s", q);
		l = strlen(q);
		h[n] = Hash(q);
		c.reset();
		for (int j = 0; j < l; ++j)
			if (isupper(q[j])) c.set(j);
		int ans = 0;
		auto rg = equal_range(o, o + n, o[n], cmp);
		for (auto i = rg.first; i < rg.second; ++i) {
			//if (!eql(dict[i], q)) continue;
			ans += (int)(d[*i] ^ c).count() <= k;
		}
		printf("%d\n", ans);
	}
	return 0;
}
