class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<double> vec(query_row + 1);
        vec[0] = poured;
        for(int i = 0; i < query_row; ++i)
            for(int j = i; j >= 0; --j) {
                double rem = max(vec[j] - 1.0, 0.0);
                vec[j + 1] += rem / 2;
                vec[j] = rem / 2;
            }
        return min(vec[query_glass], 1.0);
    }
};
