class Solution {
public:
    vector<vector<int>> colorRed(int size) {
        vector<vector<int> > ret;
        while(size >= 4) {
            for(int i = 1; i <= size + size - 1; i += 2)
                ret.push_back({size, i});
            ret.push_back({size - 1, 2});
            for(int i = 3; i <= size + size - 5; i += 2)
                ret.push_back({size - 2, i});
            ret.push_back({size - 3, 1});
            size -= 4;
        }
        switch(size) {
            case 0: {
                break;
            }
            case 1: {
                ret.push_back({1, 1});
                break;
            }
            case 2: {
                ret.push_back({2, 1});
                ret.push_back({2, 3});
                ret.push_back({1, 1});
                break;
            }
            case 3: {
                ret.push_back({3, 1});
                ret.push_back({3, 3});
                ret.push_back({3, 5});
                ret.push_back({2, 1});
                ret.push_back({1, 1});
                break;
            }
        }
        return ret;
    }
};
