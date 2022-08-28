class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
        for(auto &row: image) {
            reverse(row.begin(), row.end());
            for(int &x: row)
                x = !x;
        }
        return image;
    }
};
