class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& a, int k) {
        int n = a.size();
        vector<int> msk(n);
        for(int i = 0, j, p = 0; i < n; i = j) {
            for(j = i + 1; j < n && a[j - 1] >= a[j]; ++j);
            if(i + k < j) {
                p = max(p, i + k);
                for( ; p < j; ++p)
                    msk[p] |= 1;
            }
        }
        for(int i = 0, j, p = 0; i < n; i = j) {
            for(j = i + 1; j < n && a[j - 1] <= a[j]; ++j);
            if(i + k < j) {
                p = max(p, i);
                for( ; p + k < j; ++p)
                    msk[p] |= 2;
            }
        }
        vector<int> ret;
        for(int i = 0; i < n; ++i)
            if(msk[i] == 3)
                ret.push_back(i);
        return ret;
    }
};
