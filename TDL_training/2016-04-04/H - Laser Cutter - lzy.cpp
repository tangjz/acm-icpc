#include <cstring>
#include <cstdio>
#include <cmath>

#define N 300
#define sqr(x) ((x)*(x))

const double eps = 1e-8;
const double inf = 1e+8;

struct Point {int x,y;} s[N + 9], t[N + 9];

int n;
double g[N + 9][N + 9], lbx[N + 9], lby[N + 9], slk[N + 9];
int mat[N + 9];
bool usx[N + 9], usy[N + 9];
double ans;

int dcmp(double x) {
	return (x > +eps) - (x < -eps);
}

double dis(Point A, Point B) {
	return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));
}

void upg(double &a, double b) {
	if (a < b) a = b;
}

void dng(double &a, double b) {
	if (a > b) a = b;
}

bool aug(int i) {
	usx[i] = true;
	for (int j = 1; j <= n; ++j) {
		if (!usy[j]) {
			double d = g[i][j] - (lbx[i] + lby[j]);
			if (dcmp(d)) {
				dng(slk[j], d);
			} else {
				usy[j] = true;
				if (!mat[j] || aug(mat[j])) return mat[j] = i;
			}
		}
	}
	return false;
}

void adj() {
	double c = inf;
	for (int j = 1; j <= n; ++j) if (!usy[j]) dng(c, slk[j]);
	for (int i = 1; i <= n; ++i) if (usx[i]) lbx[i] += c;
	for (int j = 1; j <= n; ++j) {
		if (usy[j]) lby[j] -= c;
		else slk[j] -= c;
	}
}

int main() {
	scanf("%d%*d%*d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d%d", &s[i].x, &s[i].y, &t[i].x, &t[i].y);
		ans += dis(s[i], t[i]);
	}
	for (int i = 1; i <= n; ++i) {
		lbx[i] = inf;
		for (int j = 1; j <= n; ++j) {
			g[i][j] = dis(t[i], s[j]);
			dng(lbx[i], g[i][j]);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) slk[j] = inf;
		LOOP: {
			memset(usx, 0, sizeof usx);
			memset(usy, 0, sizeof usy);
			if (aug(i)) continue;
			else adj();
		} goto LOOP;
	}
	for (int j = 1; j <= n; ++j) ans += g[mat[j]][j];
	printf("%.8f\n", ans);
	return 0;
}
