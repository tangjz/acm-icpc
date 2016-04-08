/*
 * x,y轴上有4个点(0,r) (0,-r) (r,0) (-r,0)
 * 需要找到所有的x^2 + y^2 = r^2对数
 * 计算得到第一象限内的对数乘4
 * 利用勾股数的相关知识： 
 * 如果a, b, c 满足 a^2 + b^2 = c^2
 * 那么(m > n)
 * a = m^2 - n^2
 * b  = 2 * m * n
 * c = m^2 + n^2
 * gcd(n,m) = 1的情况可以得到gcd(a,b,c) = 1的数对,且这些数对的倍数(ka,kb,kc),也满足 
 * 于是枚举n, m 然后判断统计就可以了
 */
#include <iostream>
using namespace std;
const int maxn = 1 << 18;
struct Hash{ int next, num, value; } hash[maxn << 1];
bool flag[maxn];
int r, top = maxn;
int gcd(int a,int b) { if(!b) return a; return gcd(b, a % b); }
void ins(int x,int value)
{
     int key = x & (maxn - 1);
     if(!flag[key])
     {
          flag[key] = true;
          hash[key].next = -1;
          hash[key].num = x;
          hash[key].value = value;
          return;
     }
     while(hash[key].next != -1) key = hash[key].next;
     hash[key].next = ++top;
     hash[top].next = -1;
     hash[top].num = x;
     hash[top].value = value;
     return;
}
inline int find(int x)
{
    int key = x & (maxn - 1);
    if(!flag[key]) return -1;
    while(key != -1)
    {
        if(hash[key].num == x) return hash[key].value;
        key = hash[key].next;
    }
    return -1;
}
int main()
{
    int i, tmp, n, m, ans = 4, c = 0;
    cin >> r;
    for(i = 1; i <= 40000; ++i) ins(i * i, i);
    for(i = 1; i * i <= r; ++i)
    {
        if(r % i != 0) continue;
        tmp = i;
        if(tmp != 1 && tmp % 4 == 1)
        {
            n = 1;
            while(1)
            {
                int nsq = n * n;
                if(nsq >= tmp) break;
                nsq = tmp - nsq;
                m = find(nsq);
                if(m > 0 && m > n && gcd(n,m) == 1) ++c;
                ++n;
            }
        }
        tmp = r / i;
        if(tmp != 1 && tmp % 4 == 1)
        {
            n = 1;
            while(1)
            {
                int nsq = n * n;
                if(nsq >= tmp) break;
                nsq = tmp - nsq;
                m = find(nsq);
                if(m > 0 && m > n && gcd(n,m) == 1) ++c;
                ++n;
            }
        }
    }
    ans += c << 3;
    cout << ans << endl;
    return 0;
}
