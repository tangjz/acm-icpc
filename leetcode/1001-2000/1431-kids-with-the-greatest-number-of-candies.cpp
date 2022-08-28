class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int mx = 0;
        for(int x : candies)
            mx = max(mx, x);
        vector<bool> ret;
        for(int x : candies)
            ret.push_back(x + extraCandies >= mx ? true : false);
        return ret;
    }
};
