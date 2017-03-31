9#include <cstdio>
#include <cstring>
const int maxn = 1000010;
char s[maxn];
int cnt, tran[256], len, x[maxn], y[maxn], c[maxn], sa[maxn], sum[maxn], l[maxn], r[maxn];
int min(int x, int y)
{
    return x < y ? x : y;
}
int main()
{
    scanf("%s", s);
    len = strlen(s);
    for(int i = 0; i < len; ++i)
    {
        if(!tran[s[i]])
        {
            ++cnt;
            tran[s[i]] = 1;
        }
    }
    for(int i = 0, j = 0; i < 256; ++i)
        if(tran[i]) tran[i] = j++;
    for(int i = 0; i < len; ++i)
        ++c[x[i] = tran[s[i]]];
    for(int i = 1; i < cnt; ++i)
        c[i] += c[i - 1];
    for(int i = len - 1; i >= 0; --i)
        sa[--c[x[i]]] = i;
    for(int k = 1; k <= len; k <<= 1)
    {
        int tmp = 0;
        for(int i = 0; i < len; ++i)
            y[tmp++] = (sa[i] + len - k) % len;
        memset(c, 0, sizeof c);
        for(int i = 0; i < len; ++i)
            ++c[x[y[i]]];
        for(int i = 1; i < cnt; ++i)
            c[i] += c[i - 1];
        for(int i = len - 1; i >= 0; --i)
            sa[--c[x[y[i]]]] = y[i];
        memcpy(y, x, sizeof x);
        cnt = 1;
        x[sa[0]] = 0;
        for(int i = 1; i < len; ++i)
            if(y[sa[i - 1]] == y[sa[i]] && y[(sa[i - 1] + k) % len] == y[(sa[i] + k) % len]) x[sa[i]] = cnt - 1;
            else x[sa[i]] = cnt++;
        if(cnt >= len) break;
    }
    for(int i = 0; i < len; ++i)
        sum[i + 1] = sum[i] + (s[i] == '(' ? 1 : -1);
    l[0] = sum[0];
    for(int i = 1; i <= len; ++i)
        l[i] = min(l[i - 1], sum[i - 1]);
    r[len] = sum[len];
    for(int i = len - 1; i >= 0; --i)
        r[i] = min(r[i + 1], sum[i]);
    for(int i = 0; i < len; ++i)
    {
        int pos = sa[i];
        int now = min(r[pos] - sum[pos], sum[len] - sum[pos] + l[pos]);
        if(sum[len] > 0 && now >= 0)
        {
            for(int j = pos; j < len; ++j)
                putchar(s[j]);
            for(int j = 0; j < pos; ++j)
                putchar(s[j]);
            for(int j = 0; j < sum[len]; ++j)
                putchar(')');
            putchar('\n');
            break;
        }
        else if(sum[len] <= 0 && now - sum[len] >= 0)
        {
            for(int j = 0; j < -sum[len]; ++j)
                putchar('(');
            for(int j = pos; j < len; ++j)
                putchar(s[j]);
            for(int j = 0; j < pos; ++j)
                putchar(s[j]);
            putchar('\n');
            break;
        }
    }
    return 0;
}
