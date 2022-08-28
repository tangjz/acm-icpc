class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        const int INF = 0x3f3f3f3f;
        int sum = 0, low[3][2];
        memset(low, 0x3f, sizeof low);
        for(int x : nums) {
            sum += x;
            int *Low = low[x % 3];
            if(Low[0] > x)
                swap(Low[0], x);
            if(Low[1] > x)
                swap(Low[1], x);
        }
        int ans = 0, rem = sum % 3;
        if(rem > 0) {
            if(low[rem][0] != INF)
                ans = max(ans, sum - low[rem][0]);
            if(low[3 - rem][1] != INF)
                ans = max(ans, sum - low[3 - rem][0] - low[3 - rem][1]);
        } else {
            ans = sum;
        }
        return ans;
    }
};
