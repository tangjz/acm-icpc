#include <cstdio>
#include <iostream>

using namespace std;

int n, x0, y0;
int x, y;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> n >> x0 >> y0;
	while (n--) {
		cin >> x >> y;
		x -= x0, y -= y0;
		cout << x + y + x0 << ' ' << y0 - x << endl;
	}
	return 0;
}
