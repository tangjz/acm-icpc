#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int len;
char buf[maxn];
inline bool isVowel(char ch) {
	return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y';
}
int main() {
	scanf("%*d%s", buf);
	for(int i = 0; buf[i]; ++i)
		if(!len || !isVowel(buf[i]) || !isVowel(buf[len - 1]))
			buf[len++] = buf[i];
	buf[len] = '\0';
	puts(buf);
	return 0;
}
