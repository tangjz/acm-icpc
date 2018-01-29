#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
char buf[maxn], trans[255];
int main() {
	int ctr = 0;
	trans['I'] = 'V';
	trans['V'] = 'X';
	trans['X'] = 'L';
	trans['L'] = 'C';
	trans['C'] = 'D';
	trans['D'] = 'M';
	while(scanf("%s", buf) == 1) {
		int top = 0;
		for(int i = 0; buf[i]; ++i) {
			buf[top++] = buf[i];
			if(top >= 4 && (buf[top - 1] == 'I' || buf[top - 1] == 'X' || buf[top - 1] == 'C')
			&& buf[top - 1] == buf[top - 2] && buf[top - 2] == buf[top - 3] && buf[top - 3] == buf[top - 4]) {
				ctr += 2;
				top -= 2;
				buf[top - 1] = trans[buf[top - 1]];
			}
			if(top >= 3 && (buf[top - 2] == 'I' || buf[top - 2] == 'X' || buf[top - 2] == 'C')
			&& buf[top - 1] == trans[buf[top - 2]] && buf[top - 1] == buf[top - 3]) {
				++ctr;
				--top;
				swap(buf[top - 1], buf[top - 2]);
				buf[top - 1] = trans[buf[top - 1]];
			}
		}
		buf[top] = '\0';
		puts(buf);
	}
	printf("modified: %d\n", ctr);
	return 0;
}
