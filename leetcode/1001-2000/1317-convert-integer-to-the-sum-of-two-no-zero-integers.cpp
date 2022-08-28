class Solution {
    bool check(int x) {
        return to_string(x).find('0') == string::npos;
    }
public:
    vector<int> getNoZeroIntegers(int n) {
        for(int i = 1; i <= n - i; ++i)
            if(check(i) && check(n - i))
                return {i, n - i};
        assert(0);
    }
};
