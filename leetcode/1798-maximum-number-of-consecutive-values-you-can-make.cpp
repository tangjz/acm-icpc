class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        int ans = 1;
        sort(coins.begin(), coins.end());
        for(int x : coins) {
            if(x > ans)
                break;
            ans += x;
        }
        return ans;
    }
};
