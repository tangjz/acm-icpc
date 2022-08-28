class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(), costs.end());
        int ans = 0;
        for(int x: costs) {
            if(x > coins)
                break;
            ++ans;
            coins -= x;
        }
        return ans;
    }
};
