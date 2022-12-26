#include <cctype>
#include <iostream>
#include <string>

using namespace std;

int n, m;
string s;

string a[] = {
	"",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
};

string b[] = {
	"ten",
	"eleven",
	"twelve",
	"thirteen",
	"fourteen",
	"fifteen",
	"sixteen",
	"seventeen",
	"eighteen",
	"nineteen",
};

string c[] = {
	"",
	"ten",
	"twenty",
	"thirty",
	"forty",
	"fifty",
	"sixty",
	"seventy",
	"eighty",
	"ninety",
};

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		s.clear();
		if (n == 1000) {
			s = "onethousand";
		} else {
			if (n >= 100) {
				s += a[n / 100] + "hundred";

			}
			if (n %= 100) {
				if (!s.empty()) s += "and";
				if (10 <= n && n < 20) {
					s += b[n - 10];
				} else {
					s += c[n / 10];
					s += a[n  % 10];
				}
			}
		}
		//cout << s << endl;
		for (auto c: s) m += (bool)isalpha(c);
		cout << m << endl;
	}
	return 0;
}
