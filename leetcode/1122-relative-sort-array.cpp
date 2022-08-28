class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> ctr;
        for(int x: arr1)
            ++ctr[x];
        arr1.clear();
        for(int x: arr2) {
            for(int c = ctr[x]; c > 0; --c)
                arr1.push_back(x);
            ctr.erase(x);
        }
        arr2.clear();
        for(auto &it: ctr)
            arr2.push_back(it.first);
        sort(arr2.begin(), arr2.end());
        for(int x: arr2) {
            for(int c = ctr[x]; c > 0; --c)
                arr1.push_back(x);
            ctr.erase(x);
        }
        return arr1;
    }
};
