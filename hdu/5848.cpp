#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
mt19937 rnd;
int mod_pow(int x, int k, int p) {
	int ret = p > 1 ? 1 : 0;
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
int mod_sqrt(int x, int p) {
	if(x < 2)
		return x;
	auto is_square_root = [&](int x) {
		return mod_pow(x, (p - 1) >> 1, p) == 1;
	};
	if(!is_square_root(x))
		return -1;
	int w, y;
	do {
		w = rnd() % p;
		(y = ((LL)w * w - x) % p) < 0 && (y += p);
	} while(is_square_root(y));
	auto mod_mul = [&](pair<int, int> u, pair<int, int> v) {
		int lft = ((LL)u.first * v.first + (LL)u.second * v.second % p * y) % p;
		int rht = ((LL)u.first * v.second + (LL)u.second * v.first) % p;
		return make_pair(lft, rht);
	};
	pair<int, int> ret = make_pair(1, 0), tmp = make_pair(w, 1);
	for(int k = (p + 1) >> 1; k > 0; k >>= 1, tmp = mod_mul(tmp, tmp))
		if(k & 1)
			ret = mod_mul(ret, tmp);
	return ret.first;
}
class BSGS {
private:
	typedef pair<int, int> Info;
	int A, p;
	LL per;
	Info prd;
	vector<pair<Info, int> > seq;
	Info mod_mul(Info const &u, Info const &v) const {
		int lft = ((LL)u.first * v.first + (LL)u.second * v.second) % p;
		int rht = ((LL)u.second * v.first + (u.first + (LL)A * u.second) % p * v.second) % p;
		return make_pair(lft, rht);
	}
public:
	LL init(int A, int p, int size) {
		this -> A = A;
		this -> p = p;
		seq.clear();
		seq.reserve(size);
		Info tmp = make_pair(0, 1);
		seq.push_back(make_pair(make_pair(1, 0), 0));
		for(int i = 1; i < size; ++i)
			seq.push_back(make_pair(mod_mul(seq.back().first, tmp), i));
		prd = mod_mul(seq.back().first, tmp);
		sort(seq.begin(), seq.end());
		tmp = prd;
		for(per = size; ; per += size) {
			int pos = lower_bound(seq.begin(), seq.end(), make_pair(tmp, size)) - seq.begin();
			if(pos && seq[pos - 1].first == tmp) {
				per -= seq[pos - 1].second;
				break;
			}
			tmp = mod_mul(tmp, prd);
		}
		prd = make_pair(1, 0);
		tmp = make_pair(A ? p - A : 0, 1);
		for(int k = size; k > 0; k >>= 1, tmp = mod_mul(tmp, tmp))
			if(k & 1)
				prd = mod_mul(prd, tmp);
		return per;
	}
	LL find(Info x) const {
		for(LL i = 0; i < per; i += seq.size()) {
			int pos = lower_bound(seq.begin(), seq.end(), make_pair(x, 0)) - seq.begin();
			if(pos < (int)seq.size() && seq[pos].first == x)
				return i + seq[pos].second;
			x = mod_mul(x, prd);
		}
		return -1;
	}
} solver;
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int A, p, x;
		LL L, R;
		scanf("%d%d%d%lld%lld", &A, &p, &x, &L, &R);
		A %= p;
		int sft = (LL)A * x % p;
		if(sft & 1) {
			sft = (sft + p) >> 1;
		} else {
			sft >>= 1;
		}
		vector<pair<int, int> > sols;
		for(int o = 0; o < 2; ++o) {
			int res = mod_sqrt(((LL)sft * sft + (LL)x * x + (o ? p - 1 : 1)) % p, p);
			if(res == -1)
				continue;
			sols.push_back(make_pair((res + p - sft) % p, o));
			if(res)
				sols.push_back(make_pair((p - res + p - sft) % p, o));
		}
		LL ans = 0;
		if(sols.size()) {
			LL per = solver.init(A, p, (int)ceil(sqrtl(p)));
			assert(!(per & 1));
			for(pair<int, int> it : sols) {
				LL pos = solver.find(make_pair(it.first, x));
				if(pos >= 0 && (pos & 1) == it.second)
					ans += (pos <= R ? (R - pos) / per + 1 : 0) - (pos < L ? (L - 1 - pos) / per + 1 : 0);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
