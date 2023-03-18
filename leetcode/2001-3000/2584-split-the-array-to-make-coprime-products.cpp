class Solution {
public:
    int findValidSplit(vector<int>& nums) {
        int n = nums.size();
        if(n == 1)
            return -1;
        map<int, set<int> > mp;
        for(int i = 0; i < n; ++i) {
            for(int x = 2, tmp = nums[i]; x <= tmp; ++x) {
                if(x * x > tmp)
                    x = tmp;
                int c = 0;
                for( ; tmp % x == 0; tmp /= x, ++c);
                if(c)
                    mp[x].insert(i);
            }
        }
        vector<int> ctr(n + 1);
        // printf("size: %d\n", nums.size());
        for(auto &it: mp) {
            int L = *it.second.begin(), R = *it.second.rbegin();
            ++ctr[L];
            --ctr[R];
            // printf("bound %d: %d %d\n", it.first, L, R);
        }
        for(int i = 0; i < n - 1; ++i) {
            if(!ctr[i])
                return i;
            ctr[i + 1] += ctr[i];
        }
        return -1;
    }
};
