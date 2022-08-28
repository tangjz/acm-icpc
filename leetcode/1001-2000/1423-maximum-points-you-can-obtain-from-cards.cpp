class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int len = (int)cardPoints.size(), sum = 0, ans = 0;
        for(int i = 0; i < k; ++i)
            sum += cardPoints[i];
        for(int i = 0; i <= k; ++i) {
            ans = max(ans, sum);
            if(i < k)
                sum += cardPoints[len - 1 - i] - cardPoints[k - 1 - i];
        }
        return ans;
    }
};
