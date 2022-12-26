#include<cstdio>
const int gave = 300;
int save, hand;
int main()
{
	int i, out;
	for(i = 1; i <= 12; ++i)
	{
		scanf("%d",&out);
		hand += gave - out;
		if(hand < 0) break;
		save += hand / 100 * 100;
		hand %= 100;
	}
	if(i <= 12) printf("-%d\n", i);
	else printf("%d\n", hand + save + save / 5);
	return 0;
}
