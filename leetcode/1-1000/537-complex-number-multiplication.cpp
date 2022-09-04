class Solution {
public:
    string complexNumberMultiply(string num1, string num2) {
        auto decode = [&](string_view s) {
            auto pos = s.find('+');
            return make_pair(stoi(string(s.substr(0, pos))), stoi(string(s.substr(pos + 1, s.size() - pos - 2))));
        };
        auto encode = [&](int r, int i) {
            static char buf[19];
            sprintf(buf, "%d+%di", r, i);
            return (string)buf;
        };
        int r1, i1, r2, i2;
        tie(r1, i1) = decode(num1);
        tie(r2, i2) = decode(num2);
        return encode(r1 * r2 - i1 * i2, r1 * i2 + r2 * i1);
    }
};
