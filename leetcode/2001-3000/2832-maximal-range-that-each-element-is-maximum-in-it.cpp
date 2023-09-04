class Solution {
public:
    vector<int> maximumLengthOfRanges(vector<int>& A) {
        int n = A.size();
        vector<int> pL(n), pR(n), res(n);
        for(int i = 0; i < n; ++i)
            for(pL[i] = i - 1; pL[i] >= 0 && A[i] >= A[pL[i]]; pL[i] = pL[pL[i]]);
        for(int i = n - 1; i >= 0; --i) {
            for(pR[i] = i + 1; pR[i] < n && A[i] >= A[pR[i]]; pR[i] = pR[pR[i]]);
            res[i] = pR[i] - pL[i] - 1;
        }
        return res;
    }
};