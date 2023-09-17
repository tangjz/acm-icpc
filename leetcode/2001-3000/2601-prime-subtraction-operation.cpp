class Solution {
public:
    bool primeSubOperation(vector<int>& nums) {
        static const int maxv = 1001;
        static int ptot = 0, pr[maxv] = {}, d[maxv] = {};
        if(!ptot) {
            for(int i = 2; i < maxv; ++i) {
                if(!d[i])
                    pr[ptot++] = d[i] = i;
                for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
                    d[k] = pr[j];
                    if(d[i] == pr[j])
                        break;
                }
            }
            d[1] = -1;
            for(int i = 2; i < maxv; ++i)
                d[i] = d[i] == i ? i : d[i - 1];
        }
        int las = 0;
        for(int x: nums) {
            if(x <= las)
                return 0;
            if(x - 2 > las)
                x -= d[x - las - 1];
            las = x;
        }
        return 1;
    }
};
