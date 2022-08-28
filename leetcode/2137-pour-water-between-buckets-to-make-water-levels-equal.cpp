class Solution {
public:
    double equalizeWater(vector<int>& buckets, int loss) {
        typedef long long LL;
        int n = buckets.size();
        if(n == 1)
            return buckets.back();
        sort(buckets.begin(), buckets.end());
        vector<LL> psum = {0};
        for(int x: buckets)
            psum.push_back(psum.back() + x);
        for(int i = n - 1; i > 0; --i) {
            LL lft = (LL)i * buckets[i - 1] - psum[i];
            LL rht = psum[n] - psum[i] - (LL)(n - i) * buckets[i - 1];
            LL rem = rht * (100 - loss) - lft * 100;
            if(rem >= 0) {
                double adt = (double)rem / (i * 100 + (n - i) * (100 - loss));
                return buckets[i - 1] + adt;
            }
        }
        return 0;
    }
};
