/*
 * 引用 THU 张昆玮 的证明：
 * 任意取出一个能使层数最高的方案，设有Ca层，其中从下往上每一层最大的块编号为Ai
 * 任取一个能使底边最短的方案，设有Cb层，其中从下往上每一层最大的块编号为Bi
 * 显然A1>=B1,ACb<=BCb，这说明至少存在一个k属于(1,CB)，满足Ak-1>=Bk-1且Ak<=Bk
 * 也就是说，方案A第k层完全被方案B第k层包含
 * 构造一个新方案，第k层往上按方案A，往下按方案B，两边都不要的块放中间当第k层
 * 新方案的层数与A相同，而底边长度与B相同
 *
 * 利用sum记录前缀和方便计算
 * f[i]表示i~n最下层最小宽度 g[i]表示i的层数
 * f[i] = min{sum[j - 1] – sum[i - 1]} (sum[j - 1] – sum[i - 1] >= f[j])
 * 用单调队列维护j :
 * 若sum[q[head + 1] – 1] – sum[i - 1] >= f[q[head + 1]] 删去队首
 * 若sum[j' - 1] – f[j'] >= sum[j - 1] – f[j]，且j > j' 删去队尾
 */
#include <iostream>
using namespace std;
int n, sum[100001] = {}, f[100001] = {}, g[100001] = {};
int q[100001] = {}, head = 0, tail = 0;
int main()
{
    int i;
    ios::sync_with_stdio(false);
    cin >> n;
    for(i = 1; i <= n; ++i)
    {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }
    q[head] = n + 1;
    for(i = n; i >= 1; --i)
    {
        while(head < tail && sum[q[head + 1] - 1] - f[q[head + 1]] >= sum[i - 1]) ++head;
        f[i] = sum[q[head] - 1] - sum[i - 1];
        g[i] = g[q[head]] + 1;
        while(head <= tail && sum[i - 1] - f[i] >= sum[q[tail] - 1] - f[q[tail]]) --tail;
        q[++tail] = i;
    }
    cout << g[1] << endl;
    return 0;
}
