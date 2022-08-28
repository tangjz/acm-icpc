class Solution {
public:
    vector<int> constructArray(int n, int k) {
        int L = 1, R = n;
        bool onLeft = 0;
        vector<int> ret;
        while(R > k + 1)
            ret.push_back(R--);
        while(L <= R) {
            if(onLeft) {
                ret.push_back(L++);
            } else {
                ret.push_back(R--);
            }
            onLeft = !onLeft;
        }
        return ret;
    }
};
