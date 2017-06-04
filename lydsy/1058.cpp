#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 500001;
int n, m, fir[maxn], las[maxn], gp = ~0u >> 1;
multiset<int> sp, tp;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", fir + i);
		las[i] = fir[i];
		multiset<int>::iterator it = sp.insert(fir[i]), jt = it;
		if((it--) != sp.begin())
			gp = min(gp, fir[i] - *it);
		if((++jt) != sp.end())
			gp = min(gp, *jt - fir[i]);
		if(i > 1)
			tp.insert(abs(fir[i] - fir[i - 1]));
	}
	while(m--) {
		char op[13];
		scanf("%s", op);
		if(op[0] == 'I') {
			int x, y;
			scanf("%d%d", &x, &y);
			multiset<int>::iterator it = sp.insert(y), jt = it;
			if((it--) != sp.begin())
				gp = min(gp, y - *it);
			if((++jt) != sp.end())
				gp = min(gp, *jt - y);
			if(x < n) {
				tp.erase(tp.find(abs(las[x] - fir[x + 1])));
				tp.insert(abs(las[x] - y));
				tp.insert(abs(y - fir[x + 1]));
			}
			las[x] = y;
		} else if(op[4] == 'G') {
			printf("%d\n", *tp.begin());
		} else {
			printf("%d\n", gp);
		}
	}
	return 0;
}
