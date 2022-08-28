class Solution {
    void upd_max(int &x, int y) {
        x < y && (x = y);
    }
public:
    int maxProfit(vector<int>& prices) {
        int f[4] = {INT_MIN, 0, INT_MIN, 0};
        for(int x : prices) {
            upd_max(f[3], f[2] + x);
            upd_max(f[2], f[1] - x);
            upd_max(f[1], f[0] + x);
            upd_max(f[0], -x);
        }
        return f[3];
    }
};
