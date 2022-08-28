class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& A, vector<int>& B, int m) {
        int n = A.size(), q = B.size(), las = 0;
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        for(int i = 0, j = 0; i < n; ++i) {
            int cnt = 0;
            for( ; cnt < m && j < q && B[j] <= A[i]; ++j, ++cnt)
                las = B[j];
            if(cnt < m)
                las = A[i];
        }
        for(int i = q - 1; i >= 0; --i)
            if(las == B[i])
                --las;
        return las;
    }
};
