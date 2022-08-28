class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if(!k)
            return 0;
        int n = (int)nums.size();
        multiset<int> sp;
        for(int i = 0, j = 0; i < n; ++i) {
            if(i - j > k)
                sp.erase(sp.find(nums[j++]));
            int x = nums[i];
            auto it = sp.lower_bound(x);
            if(it != sp.end()) {
                if((unsigned)*it - x <= t)
                    return 1;
            }
            if(!sp.empty() && it != sp.begin()) {
                --it;
                if((unsigned)x - *it <= t)
                    return 1;
            }
            sp.insert(x);
        }
        return 0;
    }
};
