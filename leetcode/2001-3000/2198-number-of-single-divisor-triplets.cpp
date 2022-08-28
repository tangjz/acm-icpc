class Solution {
public:
    long long singleDivisorTriplet(vector<int>& nums) {
        unordered_map<int, int> sp;
        for(int x: nums)
            ++sp[x];
        long long ans = 0;
        for(auto &it: sp)
            for(auto &jt: sp)
                for(auto &kt: sp) {
                    int sum = it.first + jt.first + kt.first;
                    int cnt = !(sum % it.first) + !(sum % jt.first) + !(sum % kt.first);
                    if(cnt != 1)
                        continue;
                    long long ways = 1;
                    ways *= it.second--;
                    ways *= jt.second--;
                    ways *= kt.second--;
                    ans += ways;
                    ++kt.second;
                    ++jt.second;
                    ++it.second;
                }
        return ans;
    }
};
