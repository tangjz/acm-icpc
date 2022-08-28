class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if(timeSeries.empty())
            return 0;
        int ans = 0, las = timeSeries.front() - 1;
        for(int x : timeSeries) {
            int cur = max(las + 1, x);
            las = max(las, x + duration - 1);
            ans += las - cur + 1;
        }
        return ans;
    }
};
