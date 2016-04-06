#include <map>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 105, maxm = 25, maxs = 3000;
map<string, string> Hash;
int t, nm, n, m, len;
char str[maxs], tmp[maxs];
int main()
{
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case)
    {
        printf("Case #%d:\n", Case);
        scanf("%d %d\n", &n, &m);
        len = 0;
        Hash.clear();
        for(int ch = getchar(); ch != '\n'; ch = getchar())
            if(ch == ' ')
            {
                if(len)
                {
                    str[len] = '\0';
                    strcpy(tmp, str);
                    sort(tmp, tmp + len);
                    Hash[(string)tmp] = (string)str;
                    //printf("Hash %s : %s\n", str, tmp);
                }
                len = 0;
            }
            else
                str[len++] = ch;
        if(len)
        {
            str[len] = '\0';
            strcpy(tmp, str);
            sort(tmp, tmp + len);
            Hash[(string)tmp] = (string)str;
            //printf("Hash %s : %s\n", str, tmp);
        }
        while(m--)
        {
            len = 0;
            for(int ch = getchar(); ch != '\n' && ch != EOF; ch = getchar())
                if(ch == ' ')
                {
                    if(len)
                    {
                        str[len] = '\0';
                        strcpy(tmp, str);
                        sort(tmp, tmp + len);
                        if(Hash.count((string)tmp))
                            printf("%s", Hash[(string)tmp].c_str());
                        else
                            printf("%s", str);
                    }
                    len = 0;
                    putchar(' ');
                }
                else
                    str[len++] = ch;
            if(len)
            {
                str[len] = '\0';
                strcpy(tmp, str);
                sort(tmp, tmp + len);
                if(Hash.count((string)tmp))
                    printf("%s", Hash[(string)tmp].c_str());
                else
                    printf("%s", str);
            }
            putchar('\n');
        }
    }
    return 0;
}
