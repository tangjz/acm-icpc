class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        sort(boxTypes.begin(), boxTypes.end(), [&](auto const &it, auto const &jt) {
            return it[1] > jt[1];
        });
        int ans = 0;
        for(auto &it: boxTypes) {
            int tmp = min(it[0], truckSize);
            ans += tmp * it[1];
            truckSize -= tmp;
        }
        return ans;
    }
};
