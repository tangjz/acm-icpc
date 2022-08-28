class Solution {
	typedef long long LL;
	typedef __int128_t int128;
	int dot(int x1, int y1, int x2, int y2) {
		return x1 * x2 + y1 * y2;
	}
	int det(int x1, int y1, int x2, int y2) {
		return x1 * y2 - y1 * x2;
	}
	pair<LL, int> getDist2(int x0, int y0, int x1, int y1, int x2, int y2) {
		int u = dot(x0 - x1, y0 - y1, x2 - x1, y2 - y1);
		int v = dot(x2 - x1, y2 - y1, x2 - x1, y2 - y1);
		if(u <= 0)
			return make_pair((LL)dot(x0 - x1, y0 - y1, x0 - x1, y0 - y1), 1);
		if(u >= v)
			return make_pair((LL)dot(x0 - x2, y0 - y2, x0 - x2, y0 - y2), 1);
		int w = det(x0 - x1, y0 - y1, x2 - x1, y2 - y1);
		return make_pair((LL)w * w, v);
	}
	int comp(pair<LL, int> lft, pair<LL, int> rht) {
		int128 res = (int128)lft.first * rht.second - (int128)rht.first * lft.second;
		return (res > 0) - (res < 0);
	}
	pair<LL, int> getMin(pair<LL, int> lft, pair<LL, int> rht) {
		return comp(lft, rht) > 0 ? rht : lft;
	}
public:
	bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
		if(x1 <= x_center && x_center <= x2 && y1 <= y_center && y_center <= y2)
			return 1;
		pair<LL, int> dis2 = getDist2(x_center, y_center, x1, y1, x1, y2);
		dis2 = getMin(dis2, getDist2(x_center, y_center, x1, y1, x2, y1));
		dis2 = getMin(dis2, getDist2(x_center, y_center, x1, y2, x2, y2));
		dis2 = getMin(dis2, getDist2(x_center, y_center, x2, y1, x2, y2));
		return comp(dis2, make_pair((LL)radius * radius, 1)) <= 0;
	}
};
