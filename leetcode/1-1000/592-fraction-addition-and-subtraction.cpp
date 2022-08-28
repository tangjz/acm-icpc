class Solution {
public:
    string fractionAddition(string expression) {
        int n = expression.size();
        pair<int, int> ret = {0, 1}, tmp = {};
        for(int i = 0, j; i < n; ) {
            bool neg = false;
            if(expression[i] == '-') {
                neg = true;
                ++i;
            } else if(expression[i] == '+') {
                ++i;
            }
            for(tmp.first = 0; i < n && isdigit(expression[i]); tmp.first = 10 * tmp.first + (expression[i++] - '0'));
            if(neg) {
                tmp.first = -tmp.first;
            }
            assert(i < n && expression[i] == '/');
            ++i;
            for(tmp.second = 0; i < n && isdigit(expression[i]); tmp.second = 10 * tmp.second + (expression[i++] - '0'));
            ret = {ret.first * tmp.second + ret.second * tmp.first, ret.second * tmp.second};
            int com = gcd(abs(ret.first), ret.second);
            ret = {ret.first / com, ret.second / com};
        }
        return to_string(ret.first) + "/" + to_string(ret.second);
    }
};
