#include <cstdio>
#include <algorithm>
using namespace std;
int x1, y1, x2, y2;
int main()
{
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    if(x1 + y1 <= max(x2, y2) || x1 <= x2 && y1 <= y2)
        puts("Polycarp");
    else
        puts("Vasiliy");
    return 0;
}
