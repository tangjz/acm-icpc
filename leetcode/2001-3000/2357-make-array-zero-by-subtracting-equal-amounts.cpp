class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        unordered_set<int> sp;
        for(int x: nums)
            if(x)
                sp.insert(x);
        return sp.size();
    }
};
