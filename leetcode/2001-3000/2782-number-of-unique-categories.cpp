/**
 * Definition for a category handler.
 * class CategoryHandler {
 * public:
 *     CategoryHandler(vector<int> categories);
 *     bool haveSameCategory(int a, int b);
 * };
 */
class Solution {
public:
    int numberOfCategories(int n, CategoryHandler* categoryHandler) {
        vector<int> seq;
        for(int i = 0; i < n; ++i) {
            bool skp = 0;
            for(int x: seq)
                if(categoryHandler -> haveSameCategory(x, i)) {
                    skp = 1;
                    break;
                }
            if(!skp)
                seq.push_back(i);
        }
        return seq.size();
    }
};