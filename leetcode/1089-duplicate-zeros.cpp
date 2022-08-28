class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        vector<int> ret;
        for(int x: arr) {
            ret.push_back(x);
            if(!x)
                ret.push_back(x);
        }
        ret.resize(arr.size());
        arr = move(ret);
    }
};
