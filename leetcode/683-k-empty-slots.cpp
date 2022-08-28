class Solution {
public:
    int kEmptySlots(vector<int>& bulbs, int k) {
        int n = bulbs.size(), ans = k ? -1 : n, cnt = k ? 0 : n - 1;
        vector<int> pL(n + 2), pR(n + 2);
        iota(pL.begin(), pL.end(), -1);
        iota(pR.begin(), pR.end(), 1);
        for(int i = n - 1; i >= 0; --i) {
            int x = bulbs[i];
            if(pL[x] > 0)
                cnt -= x - pL[x] - 1 == k;
            if(pR[x] <= n)
                cnt -= pR[x] - x - 1 == k;
            pL[pR[x]] = pL[x];
            pR[pL[x]] = pR[x];
            if(pL[x] > 0 && pR[x] <= n)
                cnt += pR[x] - pL[x] - 1 == k;
            if(cnt > 0)
                ans = i;
        }
        return ans;
    }
};
