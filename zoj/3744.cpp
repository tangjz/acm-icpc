#include <bits/stdc++.h>
using namespace std;
int main() {
	double x;
	while(scanf("%lf%*c", &x) == 1) {
		x = sqrt(x / 25);
		if(x < 1) {
			puts("0");
		} else {
			printf("%.20f\n", (double)(8 / sqrtl(7) * sqrtl(x) * sin(sqrtl(7) / 2 * log(x)) + 1));
		}
	}
	return 0;
}