#include <cstdio>
#include <cstring>
const int maxd = 26, maxs = 51;
int n, m;
bool tr[maxd][maxd];
char s[maxs], t[maxs];
int main() {
	scanf("%d%d", &n, &m);
	while(n--) {
		scanf("%s%s", s, t);
		tr[s[0] - 'a'][t[0] - 'a'] = 1;
	}
	for(int i = 0; i < maxd; ++i)
		tr[i][i] = 1;
	for(int k = 0; k < maxd; ++k)
		for(int i = 0; i < maxd; ++i)
			for(int j = 0; j < maxd; ++j)
				tr[i][j] |= tr[i][k] && tr[k][j];
	while(m--) {
		scanf("%s%s", s, t);
		bool chk = strlen(s) == strlen(t);
		for(int i = 0; chk && s[i]; ++i)
			chk &= tr[s[i] - 'a'][t[i] - 'a'];
		puts(chk ? "yes" : "no");
	}
	return 0;
}