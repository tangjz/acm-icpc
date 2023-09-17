class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        int v, r, c;
        unordered_map<int, int> ctr;
        auto clr = [&]() {
            v = -1;
            r = c = 0;
            ctr.clear();
        };
        auto inc = [&](int x) {
            if(!r) {
                v = x;
                r = 1;
            } else {
                r += x == v ? 1 : -1;
            }
            ++c;
            ++ctr[x];
        };
        auto ask = [&]() {
            return r && ctr[v] * 2 > c ? v : -1;
        };
        int n = nums.size();
        vector<int> suf(n);
        clr();
        for(int i = n - 1; i > 0; --i) {
            inc(nums[i]);
            suf[i] = ask();
        }
        clr();
        for(int i = 0; i + 1 < n; ++i) {
            inc(nums[i]);
            int pL = ask(), pR = suf[i + 1];
            if(pL == pR && pL != -1)
                return i;
        }
        return -1;
    }
};
