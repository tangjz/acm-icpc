#include <stdio.h>
#include <cstring>
const char *mon[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
const char *week[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
const int day[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main()
{
	int t;
	char str[1 << 5], buf[1 << 5];
	scanf("%d", &t);
	while(t--)
	{
		int mm, dd, wk, cnt = 0;
		scanf("%s%s", str, buf);
		for(mm = 0; mm < 12; ++mm)
			if(!strcmp(str, mon[mm]))
				break;
		for(wk = 0; wk < 7; ++wk)
			if(!strcmp(buf, week[wk]))
				break;
		for(dd = 1; dd <= day[mm]; ++dd, wk = wk + 1 < 7 ? wk + 1 : 0)
			if(wk == 5 || wk == 6)
				++cnt;
		printf("%d\n", cnt);
	}
	return 0;
}
