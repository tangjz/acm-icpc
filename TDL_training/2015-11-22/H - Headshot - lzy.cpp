#include <cstdio>
#include <cstring>

int m,n,l;
char s[109];

int main()
{
	while (gets(s))
	{
		n=strlen(s);
		m=l=0;
		s[n]=s[0];
		for (int i=0;i<n;++i)
		{
			if (s[i]=='0')
			{
				++m;
				l+=s[i+1]=='0';
			}
		}
		if (m*m==l*n) puts("EQUAL");
		else if (m*m<l*n) puts("SHOOT");
		else puts("ROTATE");
	}
    return 0;
}
