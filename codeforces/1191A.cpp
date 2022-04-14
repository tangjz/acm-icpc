#include <bits/stdc++.h>
using namespace std;
int main() {
	int x;
	scanf("%d", &x);
	int y = (1 - x) & 3;
	if(y > 2) {
		printf("%d B\n", (3 - x) & 3);
	} else {
		printf("%d A\n", y);
	}
	return 0;
}