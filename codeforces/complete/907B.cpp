#include <bits/stdc++.h>
using namespace std;
int x, y, z;
char buf[9][11];
int main() {
	for(int i = 0; i < 9; ++i)
		for(int j = 0; j < 9; j += 3)
			scanf("%s", buf[i] + j);
	scanf("%d%d", &x, &y);
	x = (x - 1) % 3;
	y = (y - 1) % 3;
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			if(buf[x * 3 + i][y * 3 + j] == '.') {
				buf[x * 3 + i][y * 3 + j] = '!';
				z = 1;
			}
	if(!z)
		for(int i = 0; i < 9; ++i)
			for(int j = 0; j < 9; ++j)
				if(buf[i][j] == '.')
					buf[i][j] = '!';
	for(int i = 0; i < 9; ++i) {
		for(int j = 0; j < 9; j += 3)
			printf("%.3s%c", buf[i] + j, " \n"[j == 6]);
		if(i % 3 == 2)
			puts("");
	}
	return 0;
}
