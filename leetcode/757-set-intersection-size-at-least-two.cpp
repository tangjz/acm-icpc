class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end(), [&](auto const &u, auto const &v) {
            return u[1] < v[1];
        });
        int ans = 0, las[2] = {-2, -1};
        for(auto &it: intervals) {
            int adt = 0;
            adt += !(it[0] <= las[0] && las[0] <= it[1]);
            adt += !(it[0] <= las[1] && las[1] <= it[1]);
            for(int i = 0; i < adt; ++i)
                for(int &x = las[i] = i ? las[i - 1] - 1 : it[1]; ; --x) {
                    bool skip = 0;
                    for(int j = adt; j < 2; ++j)
                        skip |= x == las[j];
                    if(!skip)
                        break;
                }
            if(las[0] > las[1])
                swap(las[0], las[1]);
            ans += adt;
        }
        return ans;
    }
};
