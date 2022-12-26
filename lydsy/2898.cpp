#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
	LL pos, sta1 = 0, sta2 = 0, val1 = 1, val2 = 1;
	int len1 = 1, len2 = 1;
	char buf1[31], buf2[31];
	vector<int> sum;
	scanf("%lld", &pos);
	while(1) {
		LL cnt = 9;
		for(int i = 1; i < len1; ++i)
			cnt *= 10;
		if(sta1 + cnt * len1 >= pos)
			break;
		sta1 += cnt * (len1++);
		val1 += cnt;
	}
	do {
		LL adt = (pos - 1 - sta1) / len1;
		sta1 += adt * len1;
		val1 += adt;
		assert(sprintf(buf1, "%lld", val1) == len1);
	} while(0);
	while(1) {
		static LL las = 0;
		LL cnt = 1, tmp;
		for(int i = 0; i < len2; ++i)
			cnt *= 10;
		tmp = (LL)sqrtl(cnt - 1);
		for( ; tmp * tmp < cnt; ++tmp);
		for( ; tmp * tmp >= cnt; --tmp);
		cnt = tmp - las;
		las = tmp;
		if(sta2 + cnt * len2 >= pos)
			break;
		sta2 += cnt * (len2++);
		val2 += cnt;
	}
	do {
		LL adt = (pos - 1 - sta2) / len2;
		sta2 += adt * len2;
		val2 += adt;
		assert(sprintf(buf2, "%lld", val2 * val2) == len2);
	} while(0);
	for(int i = 0; ; ++i) {
		while(sta1 + len1 < pos + i) {
			sta1 += len1;
			len1 = sprintf(buf1, "%lld", ++val1);
		}
		while(sta2 + len2 < pos + i) {
			sta2 += len2;
			++val2;
			len2 = sprintf(buf2, "%lld", val2 * val2);
		}
		int lft = buf1[pos + i - sta1 - 1] - '0';
		int rht = buf2[pos + i - sta2 - 1] - '0';
		sum.push_back(lft + rht);
		for(int j = (int)sum.size() - 1; j >= 0 && sum[j] >= 10; --j) {
			sum[j] -= 10;
			if(j)
				++sum[j - 1];
		}
		if(i && sum.back() < 9)
			break;
	}
	printf("%d\n", sum.front());
	return 0;
}
