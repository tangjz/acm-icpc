class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int L = 0, R = max(abs(arr.front() - x), abs(arr.back() - x));
        while(L < R) {
            int M = (L + R) >> 1;
            int cnt = upper_bound(arr.begin(), arr.end(), x + M) - lower_bound(arr.begin(), arr.end(), x - M);
            if(cnt < k) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        if(!L)
            return vector<int>(k, x);
        auto pL = lower_bound(arr.begin(), arr.end(), x - L);
        auto pR = upper_bound(arr.begin(), arr.end(), x + L);
        if(pR - pL > k) {
            auto qL = lower_bound(arr.begin(), arr.end(), x - (L - 1));
            auto qR = upper_bound(arr.begin(), arr.end(), x + (L - 1));
            int cnt = qR - qL, rem = min((int)(qL - pL), k - cnt);
            pL = qL - rem;
            cnt += rem;
            rem = min((int)(pR - qR), k - cnt);
            pR = qR + rem;
        }
        return vector<int>(pL, pR);
    }
};
