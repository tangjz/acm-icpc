class Solution {
public:
    int minimumRefill(vector<int>& plants, int capA, int capB) {
        int n = plants.size(), ans = 0;
        int curA = capA, curB = capB;
        for(int i = 0, j = n - 1; i <= j; ++i, --j) {
            if(i == j) {
                if(curA >= curB) {
                    ans += curA < plants[i];
                } else {
                    ans += curB < plants[i];
                }
                continue;
            }
            if(curA < plants[i]) {
                ++ans;
                curA = capA;
            }
            curA -= plants[i];
            if(curB < plants[j]) {
                ++ans;
                curB = capB;
            }
            curB -= plants[j];
        }
        return ans;
    }
};
