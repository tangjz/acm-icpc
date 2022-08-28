class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        unordered_map<int, int> Hash;
        for(int x : arr) {
            int r = x % k;
            ++Hash[r < 0 ? r + k : r];
        }
        for(auto &it : Hash) {
            int r = it.first;
            if(!r || r + r == k) {
                if(it.second & 1)
                    return 0;
            } else {
                auto jt = Hash.find(k - r);
                if(jt == Hash.end() || (jt -> second) != it.second)
                    return 0;
            }
        }
        return 1;
    }
};
