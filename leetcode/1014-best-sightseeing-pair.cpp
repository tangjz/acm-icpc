class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int ans = INT_MIN, pre = INT_MIN, pos = 0;
        for(int x: values) {
            if(pre > INT_MIN)
                ans = max(ans, x - pos + pre);
            pre = max(pre, x + pos);
            ++pos;
        }
        return ans;
    }
};
