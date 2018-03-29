#include <bits/stdc++.h>
const int maxn = (int)1e6 + 1;
int sLen, tLen, cnt[maxn];
char s[maxn], t[maxn], f[maxn];
int main() {
	scanf("%s%s", s, t);
	sLen = strlen(s);
	tLen = strlen(t);
	for(int i = 0; i < sLen; ++i)
		++cnt[s[i] - '0'];
	for(int i = 0; i < tLen; ++i)
		--cnt[t[i] - '0'];
	for(int nLen = 1; nLen <= 6 && nLen <= sLen - tLen; ++nLen) {
		if(sprintf(f, "%d", sLen - nLen) != nLen)
			continue;
		int n = sLen - nLen;
		bool chk = 1;
		for(int i = 0; i < nLen; ++i)
			chk &= (--cnt[f[i] - '0']) >= 0;
		if(chk && (n == 1 || t[0] != '0' || cnt[0] < n)) {
			int low = 0;
			for(int i = 1; i < 10; ++i)
				if(cnt[i]) {
					low = i;
					break;
				}
			if(low) {
				int p1 = 0, p2 = 0;
				f[p1++] = '0' + low;
				for(int i = 0; i < t[0] - '0'; ++i)
					for(int j = i == low; j < cnt[i]; ++j)
						f[p1++] = '0' + i;
				for(int i = 0; i < tLen; ++i)
					f[p1++] = t[i];
				for(int i = t[0] - '0'; i < 10; ++i)
					for(int j = i == low; j < cnt[i]; ++j)
						f[p1++] = '0' + i;
				f[p1] = '\0';
				s[p2++] = '0' + low;
				for(int i = 0; i <= t[0] - '0'; ++i)
					for(int j = i == low; j < cnt[i]; ++j)
						s[p2++] = '0' + i;
				for(int i = 0; i < tLen; ++i)
					s[p2++] = t[i];
				for(int i = t[0] - '0' + 1; i < 10; ++i)
					for(int j = i == low; j < cnt[i]; ++j)
						s[p2++] = '0' + i;
				s[p2] = '\0';
				if(strcmp(f, s) > 0)
					strcpy(f, s);
			} else {
				f[0] = '\0';
			}
			if(n == 1 || t[0] != '0') {
				int p1 = 0;
				for(int i = 0; i < tLen; ++i)
					s[p1++] = t[i];
				for(int i = 0; i < 10; ++i)
					for(int j = 0; j < cnt[i]; ++j)
						s[p1++] = '0' + i;
				s[p1] = '\0';
				if(f[0] && strcmp(s, f) > 0)
					strcpy(s, f);
			}
			puts(s);
			break;
		}
		for(int i = 0; i < nLen; ++i)
			++cnt[f[i] - '0'];
	}
	return 0;
}
