#include <cstdio>
int gcd(int a, int b) { if(!b) return a; return gcd(b, a % b); }int main(){int i, x, y, cnt = 0;scanf("%d%d", &x, &y);for(i = x; i <= y; ++i)if(x * y % i == 0 && gcd(i, x * y / i) == x) ++cnt;printf("%d\n", cnt);return 0;}
