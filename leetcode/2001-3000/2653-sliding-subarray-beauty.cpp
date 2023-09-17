class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& A, int k, int x) {
        int n = A.size();
        vector<int> ans;
        set<pair<int, int> > lft, rht;
        for(int i = 0; i < n; ++i) {
            lft.insert({A[i], i});
            if(lft.size() > x) {
                pair<int, int> key = *lft.rbegin();
                rht.insert(key);
                lft.erase(key);
            }
            if(i >= k - 1) {
                pair<int, int> key = *lft.rbegin(), pre = {A[i - k + 1], i - k + 1};
                ans.push_back(min(0, key.first));
                if(pre <= key) {
                    lft.erase(pre);
                    if(!rht.empty()) {
                        key = *rht.begin();
                        lft.insert(key);
                        rht.erase(key);
                    }
                } else {
                    rht.erase(pre);
                }
            }
        }
        return ans;
    }
};
