class Solution {
public:
    int maximumNumberOfOnes(int r, int c, int d, int k) {
        vector<int> ctr(d * d);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                ++ctr[(i % d) * d + (j % d)];
        sort(ctr.begin(), ctr.end());
        int ans = 0;
        while(k--) {
            ans += ctr.back();
            ctr.pop_back();
        }
        return ans;
    }
};
