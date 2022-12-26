#include <stdio.h>
typedef __float128 DB;
inline int sgn(DB x) {
    return (x > 0) - (x < 0);
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        long long x1, y1, x2, y2, x3, y3, x, y;
        scanf("%I64d%I64d%I64d%I64d%I64d%I64d%I64d%I64d", &x1, &y1, &x2, &y2, &x3, &y3, &x, &y);
        DB len = (DB)x * x + (DB)y * y, rem = (DB)x1 * (y2 - y3) + (DB)x2 * (y3 - y1) + (DB)x3 * (y1 - y2);
        DB len1 = (DB)x1 * x1 + (DB)y1 * y1, rem1 = (DB)x * (y3 - y2) + (DB)x2 * (y - y3) + (DB)x3 * (y2 - y);
        DB len2 = (DB)x2 * x2 + (DB)y2 * y2, rem2 = (DB)x * (y1 - y3) + (DB)x1 * (y3 - y) + (DB)x3 * (y - y1);
        DB len3 = (DB)x3 * x3 + (DB)y3 * y3, rem3 = (DB)x * (y2 - y1) + (DB)x1 * (y - y2) + (DB)x2 * (y1 - y);
        puts(sgn(len * rem + len1 * rem1 + len2 * rem2 + len3 * rem3) * sgn(rem) > 0 ? "Accepted" : "Rejected");
    }
    return 0;
}
