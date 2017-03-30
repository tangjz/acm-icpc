#include <set>
#include <string>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxs = 1001;
int n, m, tot;
set<string> Hash;
char buf[maxs];
int main()
{
	scanf("%d%d", &n, &m);
	if(n != m)
	{
		puts(n > m ? "YES" : "NO");
		return 0;
	}
	while(n--)
	{
		scanf("%s", buf);
		Hash.insert(buf);
	}
	while(m--)
	{
		scanf("%s", buf);
		if(Hash.count(buf))
			++tot;
	}
	puts(tot & 1 ? "YES" : "NO");
	return 0;
}
