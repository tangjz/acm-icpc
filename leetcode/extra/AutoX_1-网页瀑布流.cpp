class Solution {
public:
    int getLengthOfWaterfallFlow(int num, vector<int>& block) {
        multiset<int> sp;
        for(int i = 0; i < num; ++i)
            sp.insert(0);
        for(int x: block) {
            x += *sp.begin();
            sp.erase(sp.begin());
            sp.insert(x);
        }
        return *sp.rbegin();
    }
};
