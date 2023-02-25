class Solution {
public:
    long long minOperations(vector<int>& A, vector<int>& B, int k) {
        typedef long long LL;
        int n = A.size();
        if(!k) {
            for(int i = 0; i < n; ++i)
                if(A[i] != B[i])
                    return -1;
            return 0;
        }
        LL sum = 0, pos = 0, neg = 0;
        for(int i = 0; i < n; ++i) {
            int dt = B[i] - A[i];
            sum += dt;
            if(dt % k)
                return -1;
            dt /= k;
            if(dt > 0)
                pos += dt;
            else if(dt < 0)
                neg += -dt;
        }
        return sum ? -1 : max(pos, neg);
    }
};
