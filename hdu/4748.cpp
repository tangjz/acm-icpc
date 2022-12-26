#include <cmath>
#include <cstdio>
typedef double DB;
typedef long long LL;
const DB pi = acos(-1.0);
int t, R, x1, y1, z1, x2, y2, z2;
LL mode1, mode2, prd;
DB cosA, cosB, cosC, sinA, sinB, sinC;
DB cosBAC, cosABC, cosACB, BAC, ABC, ACB, ans;
void read(int &x, int prec = 2) {
    int pos1, pos2;
    static char buf[11];
    scanf("%s", buf);
    for(pos1 = 0; buf[pos1] && buf[pos1] != '.'; ++pos1);
    for(pos2 = pos1 + (buf[pos1] == '.'); prec > 0 && buf[pos2]; --prec)
        buf[pos1++] = buf[pos2++];
    while(prec-- > 0)
        buf[pos1++] = '0';
    buf[pos1] = '\0';
    sscanf(buf, "%d", &x);
}
int main() {
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        read(R);
        read(x1), read(y1), read(z1);
        read(x2), read(y2), read(z2);
        mode1 = (LL)x1 * x1 + (LL)y1 * y1 + (LL)z1 * z1;
        mode2 = (LL)x2 * x2 + (LL)y2 * y2 + (LL)z2 * z2;
        prd = (LL)x1 * x2 + (LL)y1 * y2 + (LL)z1 * z2;
        if((DB)mode1 * mode2 - (DB)(mode1 + mode2) * ((LL)R * R) <= (DB)prd * (prd - 2LL * R * R)) {
            if(prd <= (LL)R * R) { // outside
                ans = 100 - 50 * R / sqrt(mode1) - 50 * R / sqrt(mode2);
            } else { // inside
                ans = 50 - 50 * R / sqrt(mode1 < mode2 ? mode2 : mode1);
            }
        } else { // intersect
            cosA = R / sqrt(mode1);
            cosB = R / sqrt(mode2);
            cosC = prd / sqrt(mode1) / sqrt(mode2);
            sinA = sqrt(1 - cosA * cosA);
            sinB = sqrt(1 - cosB * cosB);
            sinC = sqrt(1 - cosC * cosC);
            cosBAC = (cosB - cosA * cosC) / (sinA * sinC);
            cosABC = (cosA - cosB * cosC) / (sinB * sinC);
            cosACB = (cosC - cosA * cosB) / (sinA * sinB);
            BAC = acos(cosBAC);
            ABC = acos(cosABC);
            ACB = acos(cosACB);
            ans = ((1 - cosA) * (pi - BAC) + (1 - cosB) * (pi - ABC) + ABC + BAC + ACB - pi) * 50 / pi;
        }
        printf("Case #%d: %.5f%%\n", Case, (double)ans);
    }
    return 0;
}
