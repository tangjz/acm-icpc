#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        int n, ans = 0;
        scanf("%d", &n);
        while(n--) {
            int typ = 0;
            char buf[21];
            scanf("%s", buf);
            if(!strcmp(buf, "bool") || !strcmp(buf, "char")) {
                typ = 1;
            } else if(!strcmp(buf, "int") || !strcmp(buf, "float")) {
                typ = 4;
            } else if(!strcmp(buf, "long")) {
                scanf("%s", buf);
                typ = !strcmp(buf, "long") ? 8 : 16;
            } else {
                typ = !strcmp(buf, "double") ? 8 : 16;
            }
            scanf("%s", buf);
            int len = strlen(buf), p, q;
            for(q = len - 1; q && buf[q] != ']'; --q);
            for(p = q; p && buf[p] != '['; --p);
            if(buf[p] == '[' && buf[q] == ']') {
                int num;
                buf[q] = '\0';
                sscanf(buf + p + 1, "%d", &num);
                ans += num * typ;
            } else {
                ans += typ;
            }
        }
        printf("Case #%d: %d\n", Case, (ans - 1) / 1024 + 1);
    }
    return 0;
}
