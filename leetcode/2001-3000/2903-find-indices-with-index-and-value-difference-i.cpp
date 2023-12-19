class Solution {
public:
    vector<int> findIndices(vector<int>& A, int di, int dv) {
        int n = A.size();
        pair<int, int> vL = {INT_MAX, -1}, vR = {INT_MIN, -1};
        for(int i = di; i < n; ++i) {
            pair<int, int> cur = {A[i - di], i - di};
            vL = min(vL, cur);
            vR = max(vR, cur);
            if(vL.first <= A[i] - dv)
                return {vL.second, i};
            if(vR.first >= A[i] + dv)
                return {vR.second, i};
        }
        return {-1, -1};
    }
};
