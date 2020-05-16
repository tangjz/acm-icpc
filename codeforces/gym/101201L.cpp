#include <cstdio>
#include <algorithm>
const int maxn = 51;
int n, ord[maxn];
char buf[maxn];
struct Point {
	int x, y;
	bool operator < (Point const &t) const {
		return (x < t.x) || (x == t.x && y < t.y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	int det(Point const &t) const {
		return x * t.y - y * t.x;
	}
} p[maxn];
int main() {
	int i, j, k, o;
	scanf("%d", &n);
	for(i = j = 1; i <= n; ++i) {
		scanf("%d%d", &p[i].x, &p[i].y);
		ord[i] = i;
		if(p[i] < p[j])
			j = i;
	}
	std::swap(ord[1], ord[j]);
	scanf("%s", buf);
	for(i = 2; i < n; ++i) {
		o = buf[i - 2] == 'L' ? 1 : -1;
		for(j = k = i; j <= n; ++j)
			if((p[ord[k]] - p[ord[i - 1]]).det(p[ord[j]] - p[ord[i - 1]]) * o < 0)
				k = j;
		std::swap(ord[i], ord[k]);
	}
	for(i = 1; i <= n; ++i)
		printf("%d%c", ord[i], " \n"[i == n]);
	return 0;
}
