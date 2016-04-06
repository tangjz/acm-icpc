#include <cstdio>
int ans;
bool palindrome(int x)
{
	int tmp = x, rev = 0;
	while(x) rev = rev * 10 + x % 10, x /= 10;
	return tmp == rev;
}
int main()
{
	for(int i = 100; i <= 999; ++i)
		for(int j = 100; j <= 999; ++j)
			if(palindrome(i * j)) ans = ans < i * j ? i * j : ans;
	printf("%d\n", ans);
	return 0;
}
