class Solution {
public:
    bool canChange(string A, string B) {
        int n = A.size(), j = 0;
        for(int i = 0; i < n; ++i) {
            if(A[i] == '_')
                continue;
            for( ; j < n && B[j] == '_'; ++j);
            if(j == n || A[i] != B[j])
                return 0;
            if(A[i] == 'L' && i < j)
                return 0;
            if(A[i] == 'R' && i > j)
                return 0;
            ++j;
        }
        for( ; j < n && B[j] == '_'; ++j);
        if(j < n)
            return 0;
        return 1;
    }
};
