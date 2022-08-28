class Solution {
public:
    vector<int> numsGame(vector<int>& nums) {
        const int mod = (int)1e9 + 7;
        typedef long long LL;
        int n = nums.size();
        vector<int> ret(n);
        LL sL = 0, sR = 0;
        set<pair<int, int> > lft, rht;
        for(int i = 0; i < n; ++i) {
            nums[i] -= i;
            if(lft.empty() || nums[i] < lft.rbegin() -> first) {
                lft.insert({nums[i], i});
                sL += nums[i];
            } else {
                rht.insert({nums[i], i});
                sR += nums[i];
            }
            while(rht.size() > lft.size()) {
                pair<int, int> tmp = *rht.begin();
                rht.erase(rht.begin());
                sR -= tmp.first;
                lft.insert(tmp);
                sL += tmp.first;
            }
            while(lft.size() > rht.size() + 1) {
                pair<int, int> tmp = *lft.rbegin();
                lft.erase(tmp);
                sL -= tmp.first;
                rht.insert(tmp);
                sR += tmp.first;
            }
            int mid = lft.rbegin() -> first;
            LL cost = mid * lft.size() - sL + sR - mid * rht.size();
            ret[i] = cost % mod;
        }
        return ret;
    }
};
