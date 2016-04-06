#include <cstdio>
int cnt[2];
bool win[2];
char s[5][5];
int main()
{
    for(int i = 0; i < 3; ++i) scanf("%s", s[i]);
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            if(s[i][j] == 'X') ++cnt[0];
            else if(s[i][j] == '0') ++cnt[1];
    if(cnt[0] < cnt[1] || cnt[0] > cnt[1] + 1) { puts("illegal"); return 0; }
    for(int i = 0; i < 3; ++i)
    {
        if(s[i][0] == 'X' && s[i][1] == 'X' && s[i][2] == 'X') win[0] = 1;
        if(s[i][0] == '0' && s[i][1] == '0' && s[i][2] == '0') win[1] = 1;
        if(s[0][i] == 'X' && s[1][i] == 'X' && s[2][i] == 'X') win[0] = 1;
        if(s[0][i] == '0' && s[1][i] == '0' && s[2][i] == '0') win[1] = 1;
    }
    if(s[0][0] == 'X' && s[1][1] == 'X' && s[2][2] == 'X') win[0] = 1;
    if(s[0][0] == '0' && s[1][1] == '0' && s[2][2] == '0') win[1] = 1;
    if(s[0][2] == 'X' && s[1][1] == 'X' && s[2][0] == 'X') win[0] = 1;
    if(s[0][2] == '0' && s[1][1] == '0' && s[2][0] == '0') win[1] = 1;
    if(win[0] && win[1] || win[0] && cnt[0] == cnt[1] || win[1] && cnt[0] > cnt[1]) { puts("illegal"); return 0; }
    if(win[0]) { puts("the first player won"); return 0; }
    if(win[1]) { puts("the second player won"); return 0; }
    if(cnt[0] + cnt[1] == 9) { puts("draw"); return 0; }
    puts(cnt[0] == cnt[1] ? "first" : "second");
    return 0;
}
