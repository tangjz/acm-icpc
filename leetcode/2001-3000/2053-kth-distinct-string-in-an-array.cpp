class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        unordered_map<string, int> ctr;
        for(auto &it: arr)
            ++ctr[it];
        int rem = k;
        for(auto &it: arr)
            if(ctr[it] == 1 && !(--rem))
                return it;
        return "";
    }
};
