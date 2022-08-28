class Solution {
public:
    vector<int> constructRectangle(int area) {
        int ans = max((int)floor(sqrtl(area)), 1);
        for( ; area % ans > 0; --ans);
        return {area / ans, ans};
    }
};
