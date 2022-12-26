#include <cmath>
#include <cstdio>
const double lg2 = log10(2);
int main() {
    for(int Case = 1, m; scanf("%d", &m) == 1; printf("Case #%d: %d\n", Case++, (int)(m * lg2)));
    return 0;
}
