#include <cstdio>
#include <algorithm>
using namespace std;
const int mon[][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
const char* weak[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
int n, yy, mm, dd, ww;
int spyear(int year)
{
	return year % 400 == 0 || year % 4 == 0 && year % 100 != 0;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		yy = 2000;
		mm = dd = 1;
		if(n >= 366)
		{
			++yy;
			n -= 366;
			yy += n / 146097 * 400;
			n %= 146097;
			if(n / 36524 == 4)
			{
				yy += 399;
				n = 365;
			}
			else
			{
				yy += n / 36524 * 100;
				n %= 36524;
				yy += n / 1461 * 4;
				n %= 1461;
				if(n / 365 == 4)
				{
					yy += 3;
					n = 365;
				}
				else
				{
					yy += n / 365;
					n %= 365;
				}
			}
		}
		const int *mmm = mon[spyear(yy)];
		for(int i = 1; i <= 12; ++i)
			if(n >= mmm[i])
				n -= mmm[i];
			else
			{
				mm = i;
				dd = n + 1;
				break;
			}
		printf("%04d-%02d-%02d ", yy, mm, dd);
		if(mm < 3)
		{
			--yy;
			mm += 12;
		}
		ww = (dd + mm * 2 + (mm + 1) * 3 / 5 + yy * 5 / 4 - yy / 100 + yy / 400) % 7;
		puts(weak[ww]);
	}
	return 0;
}
