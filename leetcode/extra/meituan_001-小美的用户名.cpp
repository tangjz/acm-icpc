#include <bits/stdc++.h>
using namespace std;

const int maxl = 21;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        static char buf[maxl];
        scanf("%s", buf);
        int msk = 0;
        bool bad = !isalpha(buf[0]);
        for(int i = 0; !bad && buf[i]; ++i)
            if(isalpha(buf[i])) {
                msk |= 1;
            } else if(isdigit(buf[i])) {
                msk |= 2;
            } else {
                bad = 1;
            }
        puts(!bad && msk == 3 ? "Accept" : "Wrong");
    }
    return 0;
}
