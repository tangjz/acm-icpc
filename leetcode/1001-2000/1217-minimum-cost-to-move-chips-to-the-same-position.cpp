class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        int ctr[2] = {};
        for(int x: position) {
            ++ctr[x & 1];
        }
        return min(ctr[0], ctr[1]);
    }
};
