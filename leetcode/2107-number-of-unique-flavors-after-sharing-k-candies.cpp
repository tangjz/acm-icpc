class Solution {
public:
    int shareCandies(vector<int>& candies, int k) {
        int n = candies.size(), c = 0, ans = 0;
        unordered_map<int, int> ctr;
        for(int x: candies)
            c += !(ctr[x]++);
        if(!k)
            return c;
        for(int i = 0; i < n; ++i) {
            c -= !(--ctr[candies[i]]);
            if(i >= k - 1) {
                ans = max(ans, c);
                c += !(ctr[candies[i - k + 1]]++);
            }
        }
        return ans;
    }
};
