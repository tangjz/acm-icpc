class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        int n = products.size(), m = searchWord.size(), L = 0, R = n - 1;
        vector<vector<string> > ret;
        sort(products.begin(), products.end());
        for(int i = 0; i < m; ++i) {
            for( ; L <= R && !(i < products[L].size() && products[L][i] >= searchWord[i]); ++L);
            for( ; L <= R && !(i < products[R].size() && products[R][i] <= searchWord[i]); --R);
            vector<string> row;
            for(int j = 0; j < 3 && L + j <= R; ++j)
                row.push_back(products[L + j]);
            ret.push_back(row);
        }
        return ret;
    }
};
