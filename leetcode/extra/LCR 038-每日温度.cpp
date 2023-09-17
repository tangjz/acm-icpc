class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& a) {
        int n = a.size();
        vector<int> pR(n);
        for(int i = n - 1; i >= 0; --i)
            for(pR[i] = i + 1; pR[i] < n && a[i] >= a[pR[i]]; pR[i] = pR[pR[i]]);
        for(int i = 0; i < n; ++i)
            pR[i] = pR[i] < n ? pR[i] - i : 0;
        return pR;
    }
};
