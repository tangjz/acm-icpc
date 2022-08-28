class Solution {
public:
    int distributeCandies(vector<int>& candyType) {
        int m = candyType.size() / 2;
        unordered_set<int> ctr;
        for(int x: candyType) {
            ctr.insert(x);
            if(ctr.size() >= m)
                break;
        }
        return ctr.size();
    }
};
