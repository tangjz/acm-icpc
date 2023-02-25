class Solution {
public:
    int distinctPrimeFactors(vector<int>& nums) {
        unordered_set<int> Hash;
        for(int x: nums)
            for(int i = 2; i <= x; ++i) {
                if(i * i > x)
                    i = x;
                if(x % i == 0)
                    Hash.insert(i);
                for( ; x % i == 0; x /= i);
            }
        return Hash.size();
    }
};
