class Solution {
    void rearrange(vector<int>::iterator left, vector<int>::iterator right) {
        int len = right - left;
        vector<int> tmp;
        tmp.reserve(len);
        for(vector<int>::iterator ptr = left + 1; ptr < right; ptr += 2)
            tmp.push_back(*ptr);
        for(vector<int>::iterator ptr = left; ptr < right; ptr += 2)
            tmp.push_back(*ptr);
        while(left < right) {
            *(--right) = tmp.back();
            tmp.pop_back();
        }
    }
public:
    bool isMagic(vector<int>& target) {
        int n = target.size();
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 1);
        rearrange(perm.begin(), perm.end());
        int k = 0;
        for( ; k < n && perm[k] == target[k]; ++k);
        if(!k)
            return 0;
        int p = k;
        while(p < n) {
            int q = min(p + k, n);
            rearrange(perm.begin() + p, perm.end());
            for( ; p < q && perm[p] == target[p]; ++p);
            if(p < q)
                return 0;
        }
        return 1;
    }
};
