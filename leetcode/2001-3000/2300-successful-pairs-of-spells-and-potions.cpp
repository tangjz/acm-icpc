class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        vector<int> ans;
        for(int x: spells) {
            long long low = (success - 1) / x + 1;
            if(low > potions.back()) {
                ans.push_back(0);
            } else {
                ans.push_back(potions.end() - lower_bound(potions.begin(), potions.end(), (int)low));
            }
        }
        return ans;
    }
};
