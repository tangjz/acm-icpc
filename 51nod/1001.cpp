#include <set>
#include <stdio.h>
int n, k, x;
std::set<int> s;
int main()
{
	scanf("%d%d", &k, &n);
	while(n--)
	{
		scanf("%d", &x);
		s.insert(x);
	}
	x = 0;
	for(std::set<int>::iterator it = s.begin(); it != s.end() && *it < k - *it; ++it)
		if(s.count(k - *it))
		{
			printf("%d %d\n", *it, k - *it);
			x = 1;
		}
	if(!x)
		puts("No Solution");
	return 0;
}
