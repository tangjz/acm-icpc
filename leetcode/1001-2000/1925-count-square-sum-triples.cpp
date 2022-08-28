class Solution {
public:
    int countTriples(int n) {
        vector<int> sq;
        for(int i = 0; i <= n; ++i)
            sq.push_back(i * i);
        int ans = 0;
        for(int i = 1; i <= n; ++i)
            for(int j = i, k = i; j <= n && k <= n; ++j) {
                int sum = sq[i] + sq[j];
                for( ; k <= n && sum > sq[k]; ++k);
                if(k <= n && sum == sq[k])
                    ans += 1 + (i < j);
            }
        return ans;
    }
};
