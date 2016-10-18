#include <stdio.h>
int hh, mm, hlim, mlim = 60, ans;
int main()
{
	scanf("%d%d:%d", &hlim, &hh, &mm);
	if(hh >= hlim + (hlim == 12) || hlim == 12 && !hh)
	{
		if(hlim == 24 || hh % 10 > 0)
			hh %= 10;
		else
			hh = 10;
	}
	if(mm >= mlim)
		mm %= 10;
	printf("%02d:%02d\n", hh, mm);
	return 0;
}
