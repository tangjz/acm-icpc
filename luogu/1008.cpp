#include <bits/stdc++.h>
using namespace std;

int main() {
    for(int a = 123; a <= 333; ++a) {
        int b = a + a, c = b + a;
        static char buf[11];
        int len = sprintf(buf, "%d%d%d", a, b, c);
        sort(buf, buf + len);
        len = unique(buf, buf + len) - buf;
        if(len == 9 && buf[0] != '0')
            printf("%d %d %d\n", a, b, c);
    }
    return 0;
}
