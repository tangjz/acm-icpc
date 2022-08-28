#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> vals;
    for(int x; scanf("%d%*c", &x) != EOF; vals.push_back(x));
    int n = vals.size();
    for(int i = 1; i < n; ++i)
        for(int j = 0; j < n - i; ++j)
            if(vals[j] > vals[j + 1])
                swap(vals[j], vals[j + 1]);
    for(int i = 0; i < n; ++i)
        printf("%d%c", vals[i], "\t\n"[i == n - 1]);
    return 0;
}
