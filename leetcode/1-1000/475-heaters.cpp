class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int n = heaters.size(), i = 0, ans = 0;
        for(int x: houses) {
            for( ; i < n && heaters[i] < x; ++i);
            int dis = INT_MAX;
            if(i < n)
                dis = min(dis, heaters[i] - x);
            if(i > 0)
                dis = min(dis, x - heaters[i - 1]);
            ans = max(ans, dis);
        }
        return ans;
    }
};
