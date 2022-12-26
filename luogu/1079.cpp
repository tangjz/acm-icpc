#include <cstdio>
#include <cstring>
char cipher[1024], key[128];
int main()
{
	scanf("%s%s", key, cipher);
	int i, len_key = strlen(key);
	for(i = 0; key[i]; ++i)
		if(key[i] >= 'a') key[i] -= 'a';
		else key[i] -= 'A';
	for(i = 0; cipher[i]; ++i)
		if(cipher[i] >= 'a')
			cipher[i] = (cipher[i] - 'a' - key[i % len_key] + 26) % 26 + 'a';
		else cipher[i] = (cipher[i] - 'A' - key[i % len_key] + 26) % 26 + 'A';
	printf("%s\n", cipher);
}
