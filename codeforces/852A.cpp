#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)4e5 + 1;
int n;
char buf[maxn], out[maxn];
inline int calc(int x) {
	int ret = 0;
	for( ; x > 0; ret += x % 10, x /= 10);
	return ret;
}
int main() {
	srand(time(0));
	scanf("%d%s", &n, buf);
	while(1) {
		int m = 0, sum = 0;
		for(int i = 0; i < n; ++i)
			if(i + 1 < n && rand() & 1) {
				sum += (buf[i] - '0') * 10 + (buf[i + 1] - '0');
				out[m++] = buf[i++];
				out[m++] = buf[i];
				out[m++] = '+';
			} else {
				sum += buf[i] - '0';
				out[m++] = buf[i];
				out[m++] = '+';
			}
		out[--m] = '\0';
		if(calc(calc(sum)) < 10) {
			puts(out);
			int tp = sum;
			m = sum = 0;
			for( ; tp > 0; out[m++] = '+', out[m++] = '0' + tp % 10, sum += tp % 10, tp /= 10);
			reverse(out, out + m);
			out[--m] = '\0';
			puts(out);
			tp = sum;
			m = sum = 0;
			for( ; tp > 0; out[m++] = '+', out[m++] = '0' + tp % 10, sum += tp % 10, tp /= 10);
			reverse(out, out + m);
			out[--m] = '\0';
			puts(out);
			break;
		}
	}
	return 0;
}
