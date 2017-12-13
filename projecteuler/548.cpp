#include <cstdio>
#include <algorithm>
#include <unordered_map>
typedef long long LL;
const int maxm = 15, pr[maxm] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
const int maxe = 54, maxs = 172513;
const LL maxn = (LL)1e16;
struct HashTable {
	int Counter;
	std::unordered_map<LL, int> Index;
	HashTable() : Counter(0), Index(std::unordered_map<LL, int>(maxs)) {
		newID(1);
	}
	bool count(LL const& key) const {
		return Index.count(key);
	}
	int getID(LL const& key) const {
		return Index.at(key);
	}
	int newID(LL const& key) {
		return Index[key] = Counter++;
	}
} Hash;
struct FracExp {
	int size, exp[maxm];
	void parse(LL val) { // parse and calculate sigma(val)
		size = 0;
		for(LL i = 2; i * i <= val; ++i) {
			if(val % i)
				continue;
			for(exp[size] = 0; val % i == 0; ++exp[size], val /= i);
			++size;
		}
		if(val > 1)
			exp[size++] = 1;
		exp[size] = 0;
		std::sort(exp, exp + size, std::greater<int>());
	}
	LL value() const { // get minimum represent
		LL ret = 1;
		for(int i = 0; i < size; ++i)
			for(int j = 0; j < exp[i]; ++j)
				ret *= pr[i];
		return ret;
	}
} cur, nxt;
LL f[maxs], g[maxs][maxm], ans;
int dfs(LL value) { // dfs(cur)
	if(Hash.count(value))
		return Hash.getID(value);
	int cID = Hash.newID(value), pID;
	LL sum = 0;
	for(int i = 0, k = cur.size, j = k - 1; i < cur.size; ++i, --j) {
		if(cur.exp[j] != cur.exp[k]) { // different part
			k = j;
			if(!(--cur.exp[k]))
				--cur.size;
			pID = dfs(value / pr[k]);
			if(!(cur.exp[k]++))
				++cur.size;
		}
		int o = i - (cur.exp[k] == 1);
		g[cID][i] = (sum += o < 0 ? f[pID] : g[pID][o]);
	}
	f[cID] = sum;
	for(int i = 0; i < cur.size; ++i)
		g[cID][i] += f[cID];
	return cID;
}
void pfs(int dep, int upp, LL val) {
	int cID = dfs(val);
	if(f[cID] > maxn)
		return;
	if(f[cID] >= val) {
		nxt.parse(f[cID]);
		if(val == nxt.value())
			ans += f[cID];
	}
	++cur.size;
	for(int i = 1; i <= upp && (val *= pr[dep]) <= maxn; ++i) {
		cur.exp[dep] = i;
		pfs(dep + 1, i, val);
	}
	cur.exp[dep] = 0;
	--cur.size;
}
int main() {
	f[0] = 1;
	pfs(0, maxe, 1);
	printf("%lld\n", ans);
	return 0;
}
