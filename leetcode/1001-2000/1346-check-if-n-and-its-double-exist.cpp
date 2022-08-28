class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        int cnt0 = 0;
        unordered_set<int> Hash;
        for(int x : arr) {
            Hash.insert(x);
            cnt0 += !x;
        }
        if(cnt0 > 1)
            return 1;
        for(int x : arr)
            if(x && Hash.count(x + x))
                return 1;
        return 0;
    }
};
