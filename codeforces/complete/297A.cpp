#include <cstdio>
int cnt1 = 0, cnt2 = 0;
char a[10001] = {}, b[10001] = {};
int main()
{
    int i;
    scanf("%s\n%s", a, b);
    for(i = 0; a[i] != '\0'; ++i) if(a[i] == '1') ++cnt1;
    if(cnt1 & 1) ++cnt1;
    for(i = 0; b[i] != '\0'; ++i) if(b[i] == '1') ++cnt2;
    if(cnt1 >= cnt2) printf("YES\n");
    else printf("NO\n");
    return 0;
}
