#include <cstdio>
#include <algorithm>
using namespace std;
const int trans[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};
int n, num[100001];
char ch[101];
bool vis;
int main()
{
	scanf("%d", &n);
	for(int k = 0; k < n; ++k)
	{
		scanf("%s", ch);
		for(int i = 0; ch[i]; ++i)
			if(ch[i] >= '0' && ch[i] <= '9') num[k] = (num[k] << 3) + (num[k] << 1) + ch[i] - '0';
			else if(ch[i] >= 'A' && ch[i] <= 'Z') num[k] = (num[k] << 3) + (num[k] << 1) + trans[(int)ch[i] - 'A'];
	}
	sort(num, num + n);
	for(int i = 0; i < n; ++i)
		if(num[i] == num[i + 1])
		{
			int cnt = 1;
			while(num[i] == num[i + 1]) ++i, ++cnt;
			printf("%3.3d-%4.4d %d\n", num[i] / 10000, num[i] % 10000, cnt);
			vis = 1;
		}
	if(!vis) puts("No duplicates.");
	return 0;
}