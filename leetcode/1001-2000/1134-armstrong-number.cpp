class Solution {
public:
    bool isArmstrong(int n) {
        string buf = to_string(n);
        int len = buf.size();
        long long sum = 0;
        for(char ch: buf) {
            long long x = ch - '0', prd = 1;
            for(int i = len; i > 0; i >>= 1, x *= x)
                if(i & 1)
                    prd *= x;
            sum += prd;
        }
        return sum == n;
    }
};
