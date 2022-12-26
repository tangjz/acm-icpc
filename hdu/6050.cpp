#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxd = 65, mod = 1000000007;
int t;
LL n, m;
inline void mod_inc(int &x, int y) {
    (x += y) >= mod && (x -= mod);
}
inline void mod_inc_mul(int &x, int y, int z) {
    x = (x + (LL)y * z) % mod;
}
struct Matrix {
    int r, c, num[3][3];
    Matrix operator + (const Matrix &x) const {
        Matrix ret = *this;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                mod_inc(ret.num[i][j], x.num[i][j]);
        return ret;
    }
    Matrix operator * (const Matrix &x) const {
        Matrix ret = {r, x.c};
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                for(int k = 0; k < x.c; ++k)
                    mod_inc_mul(ret.num[i][k], num[i][j], x.num[j][k]);
        return ret;
    }
    Matrix pow(LL k) const {
        Matrix ret = {r, r}, tmp = *this;
        for(int i = 0; i < r; ++i)
            ret.num[i][i] = 1;
        for( ; k > 0; k >>= 1, tmp = tmp * tmp)
            if(k & 1)
                ret = ret * tmp;
        return ret;
    }
} Sum[maxd], Mat[maxd], vec, Ans, Tmp;
int main() {
    Sum[0].r = Sum[0].c = Mat[0].r = Mat[0].c = Mat[0].num[0][1] = 2;
    Sum[0].num[0][0] = Sum[0].num[1][1] = Mat[0].num[1][0] = Mat[0].num[1][1] = 1;
    for(int i = 1; i < maxd; ++i) {
        Sum[i] = Sum[i - 1] + Mat[i - 1] * Sum[i - 1];
        Mat[i] = Mat[i - 1] * Mat[i - 1];
    }
    vec.r = vec.num[0][0] = vec.num[0][1] = 1;
    vec.c = 2;
    scanf("%d", &t);
    while(t--) {
        scanf("%I64d%I64d", &n, &m);
        Ans.r = Ans.c = Tmp.r = Tmp.c = 2;
        Ans.num[0][0] = Ans.num[0][1] = Ans.num[1][0] = Ans.num[1][1] = Tmp.num[0][1] = Tmp.num[1][0] = 0;
        Tmp.num[0][0] = Tmp.num[1][1] = 1;
        for(int j = 0; n; ++j, n >>= 1) {
            if(~n & 1)
                continue;
            Ans = Ans + Tmp * Sum[j];
            Tmp = Tmp * Mat[j];
        }
        Ans = vec * Ans.pow(m - 1);
        printf("%d\n", Ans.num[0][0]);
    }
    return 0;
}
