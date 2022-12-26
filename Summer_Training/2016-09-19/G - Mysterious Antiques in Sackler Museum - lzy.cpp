#include <iostream>
#include <algorithm>

using namespace std;

struct Rect {int x, y;};

int T;
Rect r[4], s[3];

bool get(Rect a, Rect b, Rect c) {
	if (a.x == b.x) {
		if (a.x == c.x) return true;
		if (a.x == c.y) return true;
		if (a.y + b.y == c.x) return true;
		if (a.y + b.y == c.y) return true;
	}
	swap(a.x, a.y);
	if (a.x == b.x) {
		if (a.x == c.x) return true;
		if (a.x == c.y) return true;
		if (a.y + b.y == c.x) return true;
		if (a.y + b.y == c.y) return true;
	}
	swap(b.x, b.y);
	if (a.x == b.x) {
		if (a.x == c.x) return true;
		if (a.x == c.y) return true;
		if (a.y + b.y == c.x) return true;
		if (a.y + b.y == c.y) return true;
	}
	swap(a.x, a.y);
	if (a.x == b.x) {
		if (a.x == c.x) return true;
		if (a.x == c.y) return true;
		if (a.y + b.y == c.x) return true;
		if (a.y + b.y == c.y) return true;
	}
	return false;
}

bool gao(Rect r[]) {
	if (get(r[0], r[1], r[2])) return true;
	if (get(r[1], r[2], r[0])) return true;
	if (get(r[2], r[0], r[1])) return true;
	return false;
}

bool gao() {
	int n;
	for (int i = 0; i < 4; ++i) {
		n = 0;
		for (int j = 0; j < 4; ++j)
			if (j != i) s[n++] = r[j];
		if (gao(s)) return true;
	}
	return false;
}

int main() {
	cin >> T;
	while (T--) {
		for (int i = 0; i < 4; ++i)
			cin >> r[i].x >> r[i].y;
		puts(gao() ? "Yes" : "No");
	}
	return 0;
}
