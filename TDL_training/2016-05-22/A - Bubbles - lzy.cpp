#include <cstdio>
#include <algorithm>

using namespace std;

const double eps = 1e-6;

int n, m;
pair<int, int> p[1009];
double pos[1000009];

int dcmp(double x) {
	return (x > +eps) - (x < -eps);
}

double sqr(double x) {
	return x * x;
}

bool eql(double x, double y) {
	return dcmp(x - y) == 0;
}

#define x first
#define y second

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
	sort(p, p + n);
	m = unique(p, p + n) - p;
	if (m < n) {
		puts("0");
	} else {
		m = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (p[i].x != p[j].x) {
					pos[m++] = (sqr(p[j].x) - sqr(p[i].x) + sqr(p[j].y) - sqr(p[i].y)) / 2 / (p[j].x - p[i].x);
					//printf("%f\n", x[m - 1]);
				}
			}
		}
		sort(pos, pos + m);
		m = unique(pos, pos + m, eql) - pos;
		printf("%d\n", m + 1);
	}

	return 0;
}
