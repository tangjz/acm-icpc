class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size(), m = arr2.size(), adt = 0;
        vector<int> ret;
        for(int i = 0; i < n || i < m; ++i) {
            i < n && (adt += arr1[n - 1 - i]);
            i < m && (adt += arr2[m - 1 - i]);
            ret.push_back(adt & 1);
            adt = -(adt >> 1);
        }
        if(adt < 0) {
            ret.push_back(1);
            adt = 1;
        }
        if(adt > 0) {
            ret.push_back(1);
            adt = 0;
        }
        while(ret.size() > 1 && !ret.back())
            ret.pop_back();
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
