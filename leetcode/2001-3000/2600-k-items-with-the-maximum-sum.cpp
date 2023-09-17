class Solution {
public:
    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
        int ans = 0;
        vector<pair<int, int> > seq = {{numOnes, 1}, {numZeros, 0}, {numNegOnes, -1}};
        for(auto &[c, v]: seq) {
            int t = min(c, k);
            k -= t;
            ans += t * v;
        }
        return ans;
    }
};
