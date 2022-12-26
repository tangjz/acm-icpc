#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX = 2000000000;

int N, T;
vector<int> ans;

int main()
{
	int t, i, j, k, l, x, y, z, p;
	for(i = 0, x = 1;i <= 30;i += 1, x *= 2)
	{
		for(j = 0, y = 1;j <= 18;j += 1, y *= 3)
		{
			if((long long)x * y > MAX)
				break;
			for(k = 0, z = 1;k <= 12;k += 1, z *= 5)
			{
				if((long long)x * y * z > MAX)
					break;
				for(l = 0, p = 1;l <= 10;l += 1, p *= 7)
				{
					if((long long)x * y * z * p > MAX)
						break;
					ans.push_back(x * y * z * p);
				}
			}
		}
	}
	sort(ans.begin(), ans.end());
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		scanf("%d", &N);
		printf("%d\n", *lower_bound(ans.begin(), ans.end(), N));
	}
	exit(0);
}
