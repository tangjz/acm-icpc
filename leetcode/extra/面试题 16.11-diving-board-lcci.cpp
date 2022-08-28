class Solution {
public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        if(!k)
            return {};
        if(shorter == longer)
            return {shorter * k};
        vector<int> ret(k + 1);
        ret[0] = shorter * k;
        longer -= shorter;
        for(int i = 1; i <= k; ++i)
            ret[i] = ret[i - 1] + longer;
        return ret;
    }
};
