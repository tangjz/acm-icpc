class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> vec[3];
        for(int x: nums) {
            int pos = 1 + (x > pivot) - (x < pivot);
            vec[pos].push_back(x);
        }
        vec[0].insert(vec[0].end(), vec[1].begin(), vec[1].end());
        vec[0].insert(vec[0].end(), vec[2].begin(), vec[2].end());
        return vec[0];
    }
};
