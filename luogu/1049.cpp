#include <cstdio>
int n, v, num; bool f[20001] = {}; int main() { f[0] = true; scanf("%d%d", &v, &n);	while(n--) { scanf("%d", &num); for(int i = v - num; i >= 0; --i) if(f[i]) f[i + num] = true; }	for(int i = v; i >= 0; --i) if(f[i]) { printf("%d\n", v - i); return 0; } }
