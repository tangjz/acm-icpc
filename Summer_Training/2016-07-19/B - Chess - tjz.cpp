#include <cstdio>
const int maxn = 1001, maxm = 20;
int sg[1 << maxm], pos[maxm + 1];
int t, n, ans;
int main()
{
    for(int msk = (1 << maxm) - 1; msk > 0; --msk)
    {
        for(int i = maxm - 1, last = maxm; i >= 0; --i)
            if((msk & (1 << i)))
            {
                if(last >= maxm)
                    continue;
                pos[sg[(msk ^ (1 << i)) | (1 << last)]] = msk;
            }
            else
                last = i;
        for(int i = 0; i <= maxm; ++i)
            if(pos[i] != msk)
            {
                sg[msk] = i;
                break;
            }
    }
    scanf("%d", &t);
    while(t--)
    {
        ans = 0;
        scanf("%d", &n);
        while(n--)
        {
            int c, x, msk = 0;
            scanf("%d", &c);
            while(c--)
            {
                scanf("%d", &x);
                msk |= 1 << --x;
            }
            ans ^= sg[msk];
        }
        puts(ans ? "YES" : "NO");
    }
    return 0;
}
