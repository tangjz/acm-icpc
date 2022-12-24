#include <cstdio>
const int maxn = 53;
int n, m, sum[maxn][maxn], ans;
inline void upd_min(int &x, int y) {
	x > y && (x = y);
}
inline void upd_max(int &x, int y) {
	x < y && (x = y);
}
struct Info {
	int xL, xR, yL, yR;
	void assign() {
		xL = yL = maxn;
		xR = yR = 0;
	}
	void assign(int x, int y) {
		xL = xR = x;
		yL = yR = y;
	}
	void update(Info const &t) {
		upd_min(xL, t.xL);
		upd_max(xR, t.xR);
		upd_min(yL, t.yL);
		upd_max(yR, t.yR);
	}
	bool empty() const {
		return xL > xR || yL > yR;
	}
	int area() const {
		return (xR - xL + 1) * (yR - yL + 1);
	}
	bool check() const {
		return sum[xR][yR] - sum[xL - 1][yR] - sum[xR][yL - 1] + sum[xL - 1][yL - 1] == 0;
	}
} mat[maxn][maxn], row[maxn], tmp;
int main() {
	scanf("%d%d", &n, &m);
	ans = n * m + 1;
	int tx = 0, ty = 0;
	row[0].assign();
	for(int i = 1; i <= n; ++i) {
		row[i] = row[i - 1];
		mat[i][0].assign();
		for(int j = 1; j <= m; ++j) {
			int typ;
			scanf("%d", &typ);
			sum[i][j] = 0;
			mat[i][j].assign();
			if(typ == 1) {
				++sum[i][j];
			} else if(typ == 2) {
				tx = i;
				ty = j;
				mat[i][j].assign(i, j);
				row[i].update(mat[i][j]);
			}
			sum[i][j] += sum[i][j - 1];
		}
		mat[i][m + 1].assign();
	}
	if(!tx)
		ans = 0;
	for(int i = 1; i <= tx; ++i)
		for(int j = 1; j <= m; ++j)
			sum[i][j] += sum[i - 1][j];
	for(int i = tx; i >= 1; --i) {
		for(int j = 2; j < ty; ++j)
			mat[i][j].update(mat[i][j - 1]);
		for(int j = m - 1; j > ty; --j)
			mat[i][j].update(mat[i][j + 1]);
		for(int L = ty; L >= 1; --L)
			for(int R = ty; R <= m; ++R) {
				tmp = (Info){i, tx, L, R};
				int area = tmp.area();
				if(area >= ans)
					break;
				if(!tmp.check())
					continue;
				tmp = row[i - 1];
				tmp.update(mat[i][L - 1]);
				tmp.update(mat[i][R + 1]);
				if(tmp.empty()) {
					upd_min(ans, area);
				} else if(tmp.check()) {
					area += tmp.area();
					upd_max(tmp.xL, i);
					upd_min(tmp.xR, tx);
					upd_max(tmp.yL, L);
					upd_min(tmp.yR, R);
					if(!tmp.empty())
						area -= tmp.area();
					upd_min(ans, area);
				}
			}
		for(int j = 1; j <= m; ++j)
			mat[i - 1][j].update(mat[i][j]);
	}
	printf("%d\n", ans > n * m ? -1 : ans);
	return 0;
}