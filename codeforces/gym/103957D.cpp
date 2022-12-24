#include <cstdio>
int t, a, b;
void read(int &x, int prec = 2) {
	int pos1, pos2;
	char buf[7];
	scanf("%s", buf);
	for(pos1 = 0; buf[pos1] && buf[pos1] != '.'; ++pos1);
	for(pos2 = pos1 + (buf[pos1] == '.'); prec > 0 && buf[pos2]; buf[pos1++] = buf[pos2++], --prec);
	for( ; prec > 0; buf[pos1++] = '0', --prec);
	buf[pos1] = '\0';
	sscanf(buf, "%d", &x);
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		read(a), read(b);
		printf("Case #%d: %s\n", Case, a != (b << 1) && (b == 1 || b == 10 || b == 100 || b == 1000) ? "0.02" : "0.01");
	}
	return 0;
}
