class Solution {
public:
    int maxDistance(vector<int>& a, vector<int>& b) {
        int ans = 0;
        int n = a.size(), m = b.size();
        for(int i = 0, j = 0; i < m; ++i) {
            for( ; j < n && a[j] > b[i]; ++j);
            if(j < n)
                ans = max(ans, i - j);
        }
        return ans;
    }
};
