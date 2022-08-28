class Solution {
public:
    vector<string> simplifiedFractions(int n) {
        vector<string> ret;
        for(int i = 1; i <= n; ++i)
            for(int j = i + 1; j <= n; ++j)
                if(__gcd(i, j) == 1) {
                    string buf = to_string(i) + "/" + to_string(j);
                    ret.push_back(buf);
                }
        return ret;
    }
};
