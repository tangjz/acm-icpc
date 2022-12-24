#include <cstdio>

int main() {
    int a, b;
    while(scanf("%d%d", &a, &b) == 2)
    {
        __int128_t c = a + b;
        printf("%d\n", (int)c);
    }
    return 0;
}