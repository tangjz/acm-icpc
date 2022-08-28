class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<int> dist2;
        dist2.reserve(points.size());
        for(auto &it : points) {
            int x = it[0], y = it[1];
            dist2.push_back(x * x + y * y);
        }
        nth_element(dist2.begin(), dist2.begin() + (K - 1), dist2.end());
        int upp = dist2[K - 1];
        vector<vector<int> > ret;
        ret.reserve(K);
        for(auto &it : points) {
            int x = it[0], y = it[1];
            if(x * x + y * y <= upp)
                ret.push_back(it);
        }
        return ret;
    }
};
