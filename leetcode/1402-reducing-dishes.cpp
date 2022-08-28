class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        int n = (int)satisfaction.size();
        sort(satisfaction.begin(), satisfaction.end(), greater<int>());
        int ans = 0, sum = 0, cost = 0;
        for(int i = 0; i < n; ++i) {
            sum += satisfaction[i];
            cost += sum;
            ans = max(ans, cost);
        }
        return ans;
    }
};
