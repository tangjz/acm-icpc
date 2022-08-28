class Solution {
public:
    int countElements(vector<int>& arr) {
        unordered_set<int> Hash;
        for(int x : arr)
            Hash.insert(x);
        int ans = 0;
        for(int x : arr)
            ans += Hash.find(x + 1) != Hash.end();
        return ans;
    }
};
