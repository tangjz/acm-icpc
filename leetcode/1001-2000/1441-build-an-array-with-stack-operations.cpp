class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> ret;
        auto it = target.begin();
        for(int i = 1; i <= n && it != target.end(); ++i) {
            ret.push_back("Push");
            if(*it != i) {
                ret.push_back("Pop");
            } else {
                ++it;
            }
        }
        return ret;
    }
};
