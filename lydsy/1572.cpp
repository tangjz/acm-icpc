/*
 * sort (compared by D)
 * Heap : P with D
 * Time : INF -> Now_time
 * If Time > D_i Then add(Ans, Heap.top) pop(Heap)
 */
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
priority_queue<long long, vector<long long> >q;
struct Node { int d, p; } work[100002] = {};
bool cmp(const Node& x, const Node& y) { return x.d < y.d; }
int n;
long long ans = 0;
int main()
{
    int i;
    long long now = 0x7fffffff;
    ios::sync_with_stdio(false);
    cin >> n;
    for(i = 1; i <= n; ++i) cin >> work[i].d >> work[i].p;
    ++n;
    sort(work + 1, work + n + 1, cmp);
    while(n)
    {
        while(now > work[n].d && !q.empty())
        {
            --now;
            ans += q.top();
            q.pop();
        }
        now = work[n].d;
        q.push(work[n].p);
        --n;
    }
    cout << ans << endl;
    return 0;
}
