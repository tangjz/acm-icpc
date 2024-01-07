#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int T, n, a, b, c, d;
string s;

int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		a = b = c = d = 0;
		while (n--) {
			cin >> s;
			if (s == "aa") ++a;
			else if (s == "ab") ++b;
			else if (s == "ba") ++c;
			else if (s == "bb") ++d;
		}
		s.clear();
		for (; a >= 2; a -= 2) s += "aa";
		for (; b && c; --b, --c) s += "ab";
		for (; d >= 2; d -= 2) s += "bb";
		cout << s;
		//cout << '|';
		if (a) cout << "aa";
		else if (d) cout << "bb";
		//cout << '|';
		std::reverse(s.begin(), s.end());
		cout << s << endl;
	}
	return 0;
}
