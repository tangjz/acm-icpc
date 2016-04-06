#include <map>
#include <cstdio>
#include <vector>
using namespace std;
map<int, vector<int> > Hash;
int n, m, x, k;
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", &x);
			if(Hash.find(x) == Hash.end())
				Hash[x] = vector<int>();
			Hash[x].push_back(i);
		}
		while(m--)
		{
			scanf("%d%d", &k, &x);
			if(Hash.find(x) == Hash.end() || Hash[x].size() < k)
				puts("0");
			else
				printf("%d\n", Hash[x][k - 1]);
		}
	}
	return 0;
}
