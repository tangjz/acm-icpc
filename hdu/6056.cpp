#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 61, maxs = 501, mod = 998244353;
int m, b, c, len, num[maxn], poly[maxn];
int inv[maxn], bin[maxn][maxn], pw[maxn], ppw[maxn], f[maxn][maxn][maxn];
char buf[maxs];
int main() {
    inv[1] = bin[0][0] = bin[1][0] = bin[1][1] = 1;
    for(int i = 2; i < maxn; ++i) {
        inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
        bin[i][0] = bin[i][i] = 1;
        for(int j = 1; j < i; ++j)
            (bin[i][j] = bin[i - 1][j - 1] + bin[i - 1][j]) >= mod && (bin[i][j] -= mod);
    }
    for(int Case = 1; scanf("%d%d%d%s", &m, &b, &c, buf) == 4; ++Case) {
        pw[0] = pw[1] = f[0][0][0] = 1;
        for(int i = 1; i <= m; ++i) {
            memcpy(f[i], f[i - 1], sizeof f[0]);
            pw[1] = (LL)pw[1] * b % mod;
            for(int j = 2; j <= m; ++j)
                pw[j] = (LL)pw[j - 1] * pw[1] % mod;
            for(int j = 1; j <= i; ++j)
                for(int k = 0; k <= m; ++k)
                    for(int t = 0; t <= k; ++t)
                        f[i][j][k] = (f[i][j][k] + (LL)bin[k][t] * f[i - 1][j - 1][t] % mod * pw[k - t]) % mod;
        }
        len = 1;
        num[0] = 0;
        for(int i = 0; buf[i]; ++i) {
            LL tmp = buf[i] - '0';
            for(int j = 0; j < len; ++j) {
                tmp += 10LL * num[j];
                num[j] = tmp % b;
                tmp /= b;
            }
            for( ; tmp > 0; num[len++] = tmp % b, tmp /= b);
        }
        int ans = 0, val = 0;
        for(int i = len - 1; i >= 0; --i)
            val = ((LL)val * b + num[i]) % mod;
        for(int i = 0; i <= m; ++i) {
            poly[0] = 1;
            for(int j = 1; j <= m; ++j) {
                int coeff = (val + j - 1LL) * inv[j] % mod;
                poly[j] = (LL)(mod - inv[j]) * poly[j - 1] % mod;
                for(int k = j - 1; k >= 0; --k)
                    (poly[k] = ((LL)coeff * poly[k] - (k ? (LL)poly[k - 1] * inv[j] : 0LL)) % mod) < 0 && (poly[k] += mod);
            }
            int sel = 0, dt = 0;
            ppw[0] = 1;
            for(int j = 1; j < len; ++j)
                ppw[j] = (LL)ppw[j - 1] * b % mod;
            for(int j = len - 1; j >= 0; --j)
                if(num[j] > 0) {
                    int jj = j - 1 < m ? (j ? j - 1 : 0) : m;
                    pw[0] = 1;
                    for(int k = 1; k <= m; ++k)
                        pw[k] = (LL)pw[k - 1] * dt % mod;
                    for(int k = 0; k <= m; ++k) {
                        int coeff = 0;
                        for(int t = 0; t <= k; ++t)
                            coeff = (coeff + (LL)bin[k][t] * f[jj][i - sel][t] % mod * pw[k - t]) % mod;
                        if((i & 1) && coeff)
                            coeff = mod - coeff;
                        ans = (ans + (LL)coeff * poly[k]) % mod;
                    }
                    if(sel < i && j <= m) {
                        ++sel;
                        (dt += ppw[j]) >= mod && (dt -= mod);
                        if(num[j] > 1) {
                            pw[0] = 1;
                            for(int k = 1; k <= m; ++k)
                                pw[k] = (LL)pw[k - 1] * dt % mod;
                            for(int k = 0; k <= m; ++k) {
                                int coeff = 0;
                                for(int t = 0; t <= k; ++t)
                                    coeff = (coeff + (LL)bin[k][t] * f[jj][i - sel][t] % mod * pw[k - t]) % mod;
                                if((i & 1) && coeff)
                                    coeff = mod - coeff;
                                ans = (ans + (LL)coeff * poly[k]) % mod;
                            }
                            break;
                        }
                    } else {
                        break;
                    } 
                }
            num[0] += c - 1;
            if(c - 1 < 0) {
                for(int j = 0; j + 1 < len; ++j)
                    if(num[j] < 0) {
                        num[j] += b;
                        --num[j];
                    }
                if(num[len - 1] < 0)
                    break;
                for( ; len > 1 && !num[len - 1]; --len);
            } else {
                for(int j = 0; j + 1 < len; ++j)
                    if(num[j] >= b) {
                        num[j] -= b;
                        ++num[j];
                    }
                if(num[len - 1] >= b) {
                    num[len - 1] -= b;
                    num[len++] = 1;
                }
            }
            (val = (val + c - 1) % mod) < 0 && (val += mod);
        }
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}