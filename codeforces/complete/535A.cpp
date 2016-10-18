#include <stdio.h>
const char *out[20] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char *buf[10] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
int main()
{
	int s;
	scanf("%d", &s);
	if(s < 20)
		puts(out[s]);
	else if(s % 10 == 0)
		puts(buf[s / 10]);
	else
		printf("%s-%s\n", buf[s / 10], out[s % 10]);
	return 0;
}
