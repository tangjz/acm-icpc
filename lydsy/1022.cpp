/*
 * 结论题...结论题... 
 */
#include <cstdio>
int n, sg;
int main()
{
	int t, tmp;
	scanf("%d", &t);
	while(t--)
	{
		bool flag1 = false, flag2 = true;
		sg = 0;
		scanf("%d", &n);
		while(n--)
		{
			scanf("%d", &tmp);
			sg ^= tmp;
			if(tmp > 1) { flag1 = true; flag2 = false; }
		}
		if((sg && flag1) || (!sg && flag2)) puts("John");
		else puts("Brother");
	}
	return 0;
}
