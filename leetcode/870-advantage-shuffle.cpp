class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> ret(n, -1), rem;
        set<pair<int, int> > sp;
        sort(nums1.begin(), nums1.end());
        for(int i = 0; i < n; ++i)
            sp.insert({nums2[i], i});
        while(!nums1.empty()) {
            int v = nums1.back();
            nums1.pop_back();
            auto it = sp.lower_bound({v, 0});
            if(it != sp.begin()) {
                --it;
                ret[it -> second] = v;
                sp.erase(it);
            } else {
                rem.push_back(v);
            }
        }
        for(int i = 0; i < n; ++i)
            if(ret[i] == -1) {
                ret[i] = rem.back();
                rem.pop_back();
            }
        return ret;
    }
};
