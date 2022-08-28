class Solution {
public:
    vector<int> subSort(vector<int>& array) {
        vector<int> cand(array.begin(), array.end());
        sort(cand.begin(), cand.end());
        int L = 0, R = array.size() - 1;
        for( ; L <= R && array[R] == cand[R]; --R);
        for( ; L <= R && array[L] == cand[L]; ++L);
        if(L > R)
            return {-1, -1};
        return {L, R};
    }
};
