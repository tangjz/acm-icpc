class Solution {
public:
    int countCompleteSubarrays(vector<int>& A) {
        int n = A.size();
        unordered_map<int, int> ctr;
        for(int x: A)
            ++ctr[x];
        int m = ctr.size();
        ctr.clear();
        int ans = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && ctr.size() < m; ++ctr[A[j]], ++j);
            if(ctr.size() == m)
                ans += n - j + 1;
            if(!(--ctr[A[i]]))
                ctr.erase(A[i]);
        }
        return ans;
    }
};
