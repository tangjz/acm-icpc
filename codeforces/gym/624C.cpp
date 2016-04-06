#include <cstdio>
#include <cstring>
const int maxn = 50010, maxs = 256, maxk = 120;
const char cla[maxk][10] =
{
	 "h", "he", "li", "be",  "b",  "c",  "n",  "o",  "f", "ne",
	"na", "mg", "al", "si",  "p",  "s", "cl", "ar",  "k", "ca",
	"sc", "ti",  "v", "cr", "mn", "fe", "co", "ni", "cu", "zn",
	"ga", "ge", "as", "se", "br", "kr", "rb", "sr",  "y", "zr",
	"nb", "mo", "tc", "ru", "rh", "pd", "ag", "cd", "in", "sn",
	"sb", "te",  "i", "xe", "cs", "ba", "hf", "ta",  "w", "re",
	"os", "ir", "pt", "au", "hg", "tl", "pb", "bi", "po", "at",
	"rn", "fr", "ra", "rf", "db", "sg", "bh", "hs", "mt", "ds",
	"rg", "cn", "fl", "lv", "la", "ce", "pr", "nd", "pm", "sm",
	"eu", "gd", "tb", "dy", "ho", "er", "tm", "yb", "lu", "ac",
	"th", "pa",  "u", "np", "pu", "am", "cm", "bk", "cf", "es",
	"fm", "md", "no", "lr"
};
int t, n;
char str[maxn];
bool f[maxn], a[maxs][maxs];
void init()
{
	for(int i = 0; i < maxk; ++i)
		a[(int)cla[i][0]][(int)cla[i][1]] = 1;
}
int main()
{
	init();
	scanf("%d", &t);
	while(t--)
	{
		memset(f, 0, sizeof f);
		scanf("%s", str + 1);
		n = strlen(str + 1);
		f[0] = 1;
		for(int i = 1; i <= n; ++i)
		{
			if(i > 1)
				f[i] |= a[(int)str[i - 1]][(int)str[i]] & f[i - 2];
			f[i] |= a[(int)str[i]][0] & f[i - 1];
		}
		puts(f[n] ? "YES" : "NO");
	}
	return 0;
}
