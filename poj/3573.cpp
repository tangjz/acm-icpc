#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = (int)1e3 + 1, maxc = 26, maxd = 31;

void solve() {
	static char s[maxn], t[maxn], rep[maxc + 1][maxc + 1][maxd][maxd + 2] = {};
	while(fgets(s, maxn, stdin) != NULL) {
		int n = strlen(s), m = 0;
		for(int i = 0; i < n; ) {
			for( ; i < n && !isalnum(s[i]); t[m++] = s[i++]);
			if(i == n)
				break;
			int j = i + 1;
			bool abbr = isdigit(s[i]);
			for( ; j < n && isalnum(s[j]); abbr |= isdigit(s[j++]));
			if(abbr) {
				bool bad = !isalpha(s[i]) || !isalpha(s[j - 1]);
				int cnt = 0;
				char vL = tolower(s[i]), vR = tolower(s[j - 1]);
				for(int k = i + 1; !bad && k < j - 1 && cnt < maxd; ++k) {
					bad |= !isdigit(s[k]);
					cnt = cnt * 10 + (s[k] - '0');
				}
				bad = bad || cnt >= maxd || !isalpha(rep[vL - 'a'][vR - 'a'][cnt][0]);
				if(bad) {
					for( ; i < j; t[m++] = s[i++]);
				} else {
					char *pat = rep[vL - 'a'][vR - 'a'][cnt];
					for(int k = 0; k < cnt + 2; ++k) {
						bool up = k ? (vR != s[j - 1]) : (vL != s[i]);
						t[m++] = up ? toupper(pat[k]) : pat[k];
					}
					i = j;
				}
				continue;
			}
			int cnt = j - i - 2;
			char vL = tolower(s[i]), vR = tolower(s[j - 1]);
			if(cnt >= 2 && cnt < maxd) {
				char *pat = rep[vL - 'a'][vR - 'a'][cnt];
				if(pat[0] == '\0') {
					for(int k = 0, u = i; u < j; ++k, ++u)
						pat[k] = tolower(s[u]);
					pat[j - i] = '\0';
				} else if(isalpha(pat[0])) {
					bool eq = 1;
					for(int k = 0, u = i; eq && u < j; ++k, ++u)
						eq &= pat[k] == tolower(s[u]);
					if(!eq) {
						pat[0] = ' ';
						pat[1] = '\0';
					}
				}
			}
			for( ; i < j; t[m++] = s[i++]);
		}
		t[m] = '\0';
		fputs(t, stdout);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
