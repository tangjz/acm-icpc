#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 9, maxl = 31;
long long ans;
int t, n, f[maxn], h[maxn];
char buf[maxn];
typedef struct { int fir, dif, las; } Border;
void append(vector<Border> &vec, int perL, int perR) {
	if(!vec.size()) {
		vec.push_back((Border){perL, perL, perR});
		return;
	}
	Border &tail = vec.back();
	int dif = perL - tail.las;
	if(dif == tail.dif) {
		tail.las = perR;
	} else {
		vec.push_back((Border){perL, dif, perR});
	}
}
int exgcd(int a, int b, int &x, int &y) {
	int sx = 1, sy = 0, tx = 0, ty = 1;
	while(b) {
		int q = a / b;
		swap(a, b);
		b -= a * q;
		swap(sx, tx);
		tx -= sx * q;
		swap(sy, ty);
		ty -= sy * q;
	}
	x = sx;
	y = sy;
	return a;
}
int calc(Border &u, Border &v, int w) {
	if(max(max(u.fir, v.fir), w + 1) > min(u.las, v.las))
		return 0;
	int uL = u.fir <= w ? (w - u.fir) / u.dif + 1 : 0, uR = (u.las - u.fir) / u.dif;
	int vL = (v.fir - v.las) / v.dif, vR = v.fir <= w ? -((w - v.fir) / v.fir + 1) : 0;
	if(uL > uR || vL > vR)
		return 0;
	if(uL == uR) {
		int tmp = u.fir + uL * u.dif;
		return v.fir <= tmp && tmp <= v.las && (tmp - v.fir) % v.dif == 0;
	}
	if(vL == vR) {
		int tmp = v.fir - vL * v.dif;
		return u.fir <= tmp && tmp <= u.las && (tmp - u.fir) % u.dif == 0;
	}
	int x, y, r = exgcd(u.dif, v.dif, x, y), adt = u.fir - v.fir;
	if(adt % r != 0)
		return 0;
	long long low = -maxn, upp = maxn;
	auto check = [&low, &upp](long long L, long long R, int d) {
		low = max(low, L <= 0 ? L / d : (L - 1) / d + 1);
		upp = min(upp, R >= 0 ? R / d : (R + 1) / d - 1);
	};
	check(uL - (long long)x * (-adt / r), uR - (long long)x * (-adt / r), v.dif / r);
	check((long long)y * (-adt / r) - vR, (long long)y * (-adt / r) - vL, u.dif / r);
	return low <= upp ? upp - low + 1 : 0;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%s", buf);
		n = strlen(buf);
		ans = -1;
		// appeared once
		for(int i = 0, mx = -1, id; i < n; ++i) {
			h[i] = i < mx ? min(mx - i, h[id + id - i]) : 0;
			for( ; i >= h[i] && i + h[i] + 1 < n && buf[i + h[i] + 1] == buf[i - h[i]]; ++h[i]);
			if(mx < i + h[i]) {
				mx = i + h[i];
				id = i;
			}
		}
		for(int i = 1, j = 0, c = 0; i <= n; ++i) {
			for( ; j < i - j && n - i < i - j; ++j)
				c += !j || j + h[j - 1] >= n || j - 1 - h[j - 1] < 0;
			if(i + h[i - 1] >= n || i - 1 - h[i - 1] < 0)
				ans += c;
		}
		// appeared at least twice
		for(int i = 1, j = 0; i < n; ++i) {
			for( ; j && buf[i] != buf[j]; j = f[j]);
			f[i + 1] = buf[i] == buf[j] ? ++j : 0;
		}
		vector<Border> pat, pal;
		for(int i = n; i; i = f[i]) {
			int per = n - f[i];
			if(!(per & 1))
				append(pat, per, per);
		}
		for(int i = 1; i <= n; ++i) {
			vector<Border> cur;
			// append(cur, 1, 1);
			if(i > 1 && buf[i - 2] == buf[i - 1])
				append(cur, 2, 2);
			for(Border &it : pal) {
				if(it.fir + 2 <= i && buf[i - it.fir - 2] == buf[i - 1])
					if(it.fir == it.las) {
						append(cur, it.fir + 2, it.las + 2);
					} else {
						append(cur, it.fir + 2, it.las - it.dif + 2);
					}
				if(it.fir < it.las && it.las + 2 <= i && buf[i - it.las - 2] == buf[i - 1])
					append(cur, it.las + 2, it.las + 2);
			}
			pal.swap(cur);
			int low = h[i - 1] << 1;
			for(vector<Border>::iterator it = pat.begin(), jt = pal.begin(); it != pat.end() && jt != pal.end(); ++jt) {
				for( ; it != pat.end() && it -> las <= jt -> las; ++it)
					ans += calc(*it, *jt, low);
				if(it != pat.end())
					ans += calc(*it, *jt, low);
			}
			for(vector<Border>::iterator it = pat.begin(); it != pat.end() && it -> fir <= low; ++it)
				ans += (min(it -> las, low) - (it -> fir)) / (it -> dif) + 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
