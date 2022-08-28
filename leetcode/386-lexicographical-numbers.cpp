class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> ret;
        ret.reserve(n);
        for(int x = 1; ret.size() < n; ) {
            ret.push_back(x);
            if(x * 10 <= n) {
                x *= 10;
            } else {
                while(x + 1 > n)
                    x /= 10;
                ++x;
                while(x % 10 == 0)
                    x /= 10;
            }
        }
        return ret;
    }
};
