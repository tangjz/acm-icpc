class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        unordered_set<int> ret;
        vector<int> pre, cur;
        for(int x: arr) {
            pre.swap(cur);
            cur.clear();
            for(int y: pre) {
                y |= x;
                if(cur.empty() || cur.back() != y) {
                    cur.push_back(y);
                    ret.insert(y);
                }
            }
            if(cur.empty() || cur.back() != x) {
                cur.push_back(x);
                ret.insert(x);
            }
        }
        return ret.size();
    }
};
