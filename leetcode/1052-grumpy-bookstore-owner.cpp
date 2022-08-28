class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size(), ans = 0, adt = 0;
        vector<int> psum = {0};
        for(int i = 0; i < n; ++i) {
            if(!grumpy[i]) {
                adt += customers[i];
                customers[i] = 0;
            }
            psum.push_back(psum.back() + customers[i]);
        }
        for(int i = minutes; i <= n; ++i)
            ans = max(ans, psum[i] - psum[i - minutes]);
        return ans + adt;
    }
};
