#include <cstdio>
#include <algorithm>
using namespace std;

void solve(int s, int d) {
    for(int i = 4; i >= 0; --i) {
        int cost = s * i - d * (5 - i);
        if(cost >= 0)
            continue;
        int j = i * 2 + min(i, 2);
        int tot = s * j - d * (12 - j);
        if(tot < 0) {
            puts("Deficit");
        } else {
            printf("%d\n", tot);
        }
        return;
    }
}

int main() {
    for(int s, d; scanf("%d%d", &s, &d) == 2; solve(s, d));
    return 0;
}