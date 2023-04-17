#include <bits/stdc++.h>
using namespace std;

const int maxl = 101, maxn = 101, maxm = 1701, maxc = 26;

typedef pair<int, char> Map;
typedef vector<Map> Edge;
typedef pair<int, Edge> Adj;

vector<Adj> e[maxn];
int n, m, bLen[maxn], pLen[maxm], ord[maxn], ctr[maxc + 1], rctr[maxc + 1];
char buf[maxn][maxl], pat[maxm][maxl], perm[maxc + 1];
bool bDup[maxn], pDup[maxm], bUpp[maxn][maxl], pUpp[maxn][maxl];

bool dfs(int dep) {
    if(dep == n) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < bLen[i]; ++j) {
                int o = buf[i][j] - 'a';
                buf[i][j] = perm[o];
                if(bUpp[i][j])
                    buf[i][j] = toupper(buf[i][j]);
            }
            printf("%s%c", buf[i], " \n"[i == n - 1]);
        }
        return 1;
    }
    int u = ord[dep];
    if(bDup[u])
        return dfs(dep + 1);
    for(auto &it: e[u]) {
        bool bad = 0;
        int v = it.first;
        for(auto &jt: it.second) {
            int o = jt.first;
            if(perm[o] && perm[o] != jt.second) {
                bad = 1;
                break;
            }
        }
        if(bad)
            continue;
        for(auto &jt: it.second) {
            int o = jt.first, ro = jt.second - 'a';
            if(!(ctr[o]++)) {
                bad |= (rctr[ro]++);
                perm[o] = jt.second;
            }
        }
        if(!bad && dfs(dep + 1))
            return 1;
        for(auto &jt: it.second) {
            int o = jt.first, ro = jt.second - 'a';
            if(!(--ctr[o])) {
                --rctr[ro];
                perm[o] = '\0';
            }
        }
    }
    return 0;
}

mt19937_64 rnd;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    FILE *fin = fopen("dictionary.lst", "r");
    unordered_set<string> vis;
    for( ; scanf("%s", buf[n]) == 1; ++n) {
        bLen[n] = strlen(buf[n]);
        for(int i = 0; i < bLen[n]; ++i) {
            char ch = tolower(buf[n][i]);
            bUpp[n][i] = ch != buf[n][i];
            buf[n][i] = ch;
            assert(ch >= 'a' && ch <= 'z');
        }
        bDup[n] = !vis.insert(buf[n]).second;
    }
    vis.clear();
    for( ; fscanf(fin, "%s", pat[m]) == 1; ++m) {
        pLen[m] = strlen(pat[m]);
        for(int i = 0; i < pLen[m]; ++i) {
            char ch = tolower(pat[m][i]);
            pUpp[m][i] = ch != pat[m][i];
            pat[m][i] = ch;
            assert(ch >= 'a' && ch <= 'z');
        }
        pDup[m] = !vis.insert(pat[m]).second;
    }
    fclose(fin);
    for(int i = 0; i < n; ++i) {
        ord[i] = i;
        if(bDup[i])
            continue;
        for(int j = 0; j < m; ++j) {
            if(bLen[i] != pLen[j] || pDup[j])
                continue;
            bool bad = 0;
            static Edge cur;
            static char tr[maxc + 1];
            cur.clear();
            memset(tr, 0, sizeof tr);
            for(int k = 0; k < bLen[i]; ++k) {
                int o = buf[i][k] - 'a';
                if(tr[o] && pat[j][k] != tr[o]) {
                    bad = 1;
                    break;
                }
                if(!tr[o]) {
                    tr[o] = pat[j][k];
                    cur.push_back({o, tr[o]});
                }
            }
            if(!bad) {
                shuffle(cur.begin(), cur.end(), rnd);
                e[i].push_back({j, cur});
            }
        }
        sort(e[i].begin(), e[i].end(), [&](auto const &u, auto const &v) {
            return u.second.size() > v.second.size();
        });
    }
    sort(ord, ord + n, [&](auto const &u, auto const &v) {
        int uS = e[u].size(), vS = e[v].size();
        if(!uS || !vS)
            return uS > vS;
        return e[u].front().second.size() > e[v].front().second.size();
    });
    if(!dfs(0))
        puts("No solution");
    return 0;
}
