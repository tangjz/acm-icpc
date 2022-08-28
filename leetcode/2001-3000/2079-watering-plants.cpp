class Solution {
public:
    int wateringPlants(vector<int>& plants, int capacity) {
        int n = plants.size();
        int ans = 0;
        for(int i = 0, j; i < n; i = j) {
            int cnt = 0;
            for(j = i; j < n && (cnt + plants[j]) <= capacity; cnt += plants[j++]);
            ans += (j) << (j < n);
        }
        return ans;
    }
};
