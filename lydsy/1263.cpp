/*
 * 先选3再选2或4 因为3^2 > 2^3 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5010, mod = 10;
struct Big_int
{
    int len, num[maxn];
    Big_int(void) { len = 1; fill_n(num, maxn, 0); }
    void init(const int &x) { num[0] = x; }
    Big_int operator * (const int &x) const
    {
        int i;
        Big_int tmp = *this;
        for(i = 0; i < tmp.len; ++i) tmp.num[i] *= x;
        for(i = 0; i < tmp.len; ++i)
            if(tmp.num[i] >= mod)
            {
                tmp.num[i + 1] += tmp.num[i] / mod;
                tmp.num[i] %= mod;
            }
        while(tmp.num[tmp.len])
        {
            tmp.num[tmp.len + 1] = tmp.num[len] / mod;
            tmp.num[tmp.len++] %= mod;
        }
        return tmp;
    }
    Big_int operator *= (const int &x) { return *this = *this * x; }
    void Print()
    {
        int limit = min(len, 100);
        printf("%d\n", len);
        for(int i = 1; i <= limit; ++i) printf("%d", num[len - i]);
        printf("\n");
    }
} ans;
int n;
int main()
{
    scanf("%d",&n);
    ans.init(1);
    while(n > 4)
    {
        ans *= 3;
        n -= 3;
    }
    ans *= n;
    ans.Print();
    return 0;
}
