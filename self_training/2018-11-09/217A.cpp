#include <bits/stdc++.h>
using namespace std;
int A, B, L;
int check(int x, int y) {
	for(int i = 0; ; i ^= 1) {
		if(x > L)
			return i;
		y += ((y - 1) / x + 1) * x;
		swap(x, y);
	}
}
int main() {
	scanf("%d%d%d", &A, &B, &L);
	printf("%s %s\n", check(A, B) == 0 ? "Yes" : "No", check(B, A) == 1 ? "Yes" : "No");
	return 0;
}