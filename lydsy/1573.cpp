/*
 * 设直线与圆的交点相对于向量(-1,0)的极角为l,r(l < r)
 * 直线L1和直线L2相交的充要条件是l1 ≤l2 ≤r1 ≤r2
 * 统计区间[lj,rj]里面ri的个数
 */
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
struct Line
{
    int id; double angle;
    Line(const int x, const double y) : id(x), angle(y) {}
    inline bool operator < (const Line &x) const { return angle > x.angle; }
};
vector<Line> toSort;
int n, d, c[100001], visited[50000] = {};
long long ans = 0;
int query(int x) { int ans = 0; while(x) { ans += c[x]; x -= x&-x; } return ans; }
void add(int x, const int delta) { while (x <= (n << 1)) { c[x] += delta; x += x&-x; } }
int main()
{
    int i;
    long long a, b, c, tmp, delta2;
    double tmp2, delta, x1, x2, y1, y2;
    ios::sync_with_stdio(false);
    cin >> n >> d;
    for(i = 0; i < n; ++i)
    {
        cin >> a >> b >> c;
        tmp = a * a + b * b;
        delta2 = d * d * tmp - c * c;
        if(delta2 > 0)
        {
            delta = sqrt(delta2);
            tmp2 = tmp;
            x1 = (a * c + b * delta) / tmp2;
            x2 = (a * c - b * delta) / tmp2;
            y1 = (b * c - a * delta) / tmp2;
            y2 = (b * c + a * delta) / tmp2;
            toSort.push_back(Line(i, atan2(y1, x1)));
            toSort.push_back(Line(i, atan2(y2, x2)));
        }
    }
    sort(toSort.begin(), toSort.end());
    for(vector<Line>::size_type i = 0; i < toSort.size(); ++i)
        if(visited[toSort[i].id])
        {
            ans += query(i + 1) - query(visited[toSort[i].id] + 1);
            add(visited[toSort[i].id] + 1, -1);
        }
        else
        {
            visited[toSort[i].id] = i;
            add(i + 1, 1);
        }
    cout << ans << endl;
    return 0;
}
