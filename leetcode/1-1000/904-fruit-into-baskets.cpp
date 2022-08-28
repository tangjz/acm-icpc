class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size(), m = 0, ans = 0;
        vector<int> ctr(n);
        for(int i = 0, j = 0; i < n; ++i) {
            m += !ctr[fruits[i]];
            ++ctr[fruits[i]];
            for( ; j < i && m > 2; --ctr[fruits[j]], m -= !ctr[fruits[j]], ++j);
            ans = max(ans, i - j + 1);
        }
        return ans;
    }
};
