/*
 * 某一位只和自己前面那个位的状态有关 
 * dp[i][j] 表示长度为i,最后一个数字为j的方案数 
 * dp[1][j] = 1
 * dp[i][j] = sum{ dp[i - 1][k] } (|k - j| <= 2) (i > 1)
 * 下一步是确定对于所给的长为L的数字来计算 
 * cnt[i] = sum{dp[j][k]} (1<=j<=i,0<=k<=9)
 * 接下来需要求dphead[i][j],表示长度为i的数字开头为j的方案数 
 * 方程同dp 
*/
#include <cstring>
#include <iostream>
using namespace std;
string a, b;
int dp[11][11], dphead[11][11], cnt[11];
int abs(int x) { if(x >= 0) return x; return -x;}
bool check(string s)
{
    int i, len = s.length();
    for(i = 0; i < len - 1; ++i)
        if(abs(s[i] - s[i + 1]) < 2) return false;
    return true;
}
int calc(string s)
{
    int i, j, num, tmp, last, len = s.length(), ans = 0;
    if(len == 1) return s[0] - '0';
    for(i = 0; s[i]; ++i)
    {
        num = s[i] - '0';
        if(!i)
        {
            j = 1;
            ans += cnt[len - 1];
            while(j < num) ans += dphead[len][j++];
            last = num;
        }
        else
        {
            j = 0;
            tmp = -1;
            while(j < num)
            {
                if(abs(j - last) >= 2) ans += dphead[len - i][j];
                tmp = j++;
            }
            if(i == len - 1 && abs(j - last) >= 2) ++ans;
            if(abs(j - last) >= 2) last = tmp = num;
            if(tmp < num) break;
        }
    }
    return ans;
}
void init()
{
    int i, j, k;
    for(i = 1; i <= 9; ++i) dp[1][i] = 1;
    for(i = 2; i <= 10; ++i)
        for(j = 0; j <= 9; ++j)
            for(k = 0; k <= 9; ++k)
                if(abs(k - j) >= 2) dp[i][j] += dp[i - 1][k];
    for(i = 1; i <= 10; ++i)
        for(j = 1; j <= i; ++j)
            for(k = 0; k < 10; ++k) cnt[i] += dp[j][k];
    for(i = 0; i < 10; ++i) dphead[1][i] = 1;
    for(i = 2; i <= 10; ++i)
        for(j = 0; j < 10; ++j)
            for(k = 0; k < 10; ++k)
                if(abs(j - k) >= 2) dphead[i][j] += dphead[i - 1][k];
}
int main()
{
    init();
    cin >> a >> b;
    cout << calc(b) - calc(a) + check(a) << endl;
    return 0;
}
