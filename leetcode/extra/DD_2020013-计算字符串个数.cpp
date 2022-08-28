#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    int c0 = 0, c1 = 0;
    int match = 0;
    for(char ch: s) {
        if(isalpha(ch)) {
            ++c1;
            match = 0;
        } else if(!match && ch & 0x80) {
            ++match;
        } else if(match == 1 && ch & 0x80) {
            ++match;
        } else if(match == 2) {
            match = 0;
            ++c0;
        } else {
            match = 0;
        }
    }
    printf("Number of Chinese characters:%d\nNumber of letters:%d\n", c0, c1);
    return 0;
}
