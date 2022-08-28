class Solution {
public:
    string solveEquation(string equation) {
        auto parse = [&](string const &buf) -> pair<int, int> {
            int n = buf.size(), a = 0, b = 0;
            for(int i = 0, j; i < n; ) {
                int sgn = 1;
                if(buf[i] == '+') {
                    ++i;
                } else if(buf[i] == '-') {
                    sgn = -sgn;
                    ++i;
                }
                assert(i < n);
                if(buf[i] == '0') {
                    for( ; i < n && buf[i] != '-' && buf[i] != '+'; ++i);
                    continue;
                }
                int val = 0;
                for( ; i < n && isdigit(buf[i]); ++i)
                    val = val * 10 + (buf[i] - '0');
                if(i < n && buf[i] == 'x') {
                    ++i;
                    if(!val)
                        val = 1;
                    a += sgn * val;
                } else {
                    b += sgn * val;
                }
            }
            return {a, b};
        };
        auto pos = equation.find('=');
        pair<int, int> lft = parse(equation.substr(0, pos)), rht = parse(equation.substr(pos + 1));
        lft.first -= rht.first;
        lft.second -= rht.second;
        if(!lft.first)
            return lft.second ? "No solution" : "Infinite solutions";
        return "x=" + to_string(-lft.second / lft.first);
    }
};
