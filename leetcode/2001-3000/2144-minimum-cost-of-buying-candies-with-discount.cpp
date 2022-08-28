class Solution {
public:
    int minimumCost(vector<int>& cost) {
        sort(cost.begin(), cost.end());
        reverse(cost.begin(), cost.end());
        int ans = 0, pos = 0;
        for(int x: cost) {
            if(pos < 2)
                ans += x;
            pos = (pos + 1) % 3;
        }
        return ans;
    }
};
