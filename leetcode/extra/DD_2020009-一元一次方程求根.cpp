#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    string equation;
    getline(cin, equation);
    int n = 0;
    for(char ch: equation)
        if(ch != ' ')
            equation[n++] = ch;
    assert(n >= 2 && equation[n - 1] == '0' && equation[n - 2] == '=');
    equation.resize(n - 2);
    auto pos = equation.find('x');
    assert(pos != string::npos);
    double a, b = stof(equation.substr(pos + 1));
    if(pos == 0) {
        a = 1;
    } else if(pos == 1 && !isdigit(equation[0])) {
        a = equation[0] == '-' ? -1 : 1;
    } else {
        a = stof(equation.substr(0, pos));
    }
    printf("x=%.1f\n", -b / a);
    return 0;
}
