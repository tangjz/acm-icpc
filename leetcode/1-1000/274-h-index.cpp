class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = (int)citations.size(), L = 0, R = n;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            nth_element(citations.begin() + (n - R), citations.begin() + (n - M), citations.begin() + (n - L));
            if(citations[n - M] >= M) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
