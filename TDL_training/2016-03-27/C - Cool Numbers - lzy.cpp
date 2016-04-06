#include <cstring>
#include <cstdio>
#include <algorithm>

using std::swap;

#define N 1000001

int k;
bool f[N];

char *strrev(char *s) {
	int l = strlen(s);
	for (int i = 0; i + i < l; ++i) swap(s[i], s[l - 1 - i]);
	return s;
}

int rev(int x) {
	int y;
	char buff[9];
	sprintf(buff, "%d", x);
	strrev(buff);
	sscanf(buff, "%d", &y);
	return y;
}

int main() {
	for (int i = 2; i * i < N; ++i) {
		if (!f[i]) {
			for (int j = i * i; j < N; j += i) f[j] = true;
		}
	}
	scanf("%d", &k);
	for (int i = 2; i < N ; ++i) {
		k -= i != rev(i) && !f[i] && !f[rev(i)];
		if (!k) {
			printf("%d\n", i);
			break;
		}
	}
	if (k) puts("-1");
	return 0;
}
