class Excel {
    int r, c;
    vector<pair<int, map<int, int> > > vals;
    int getVal(int idx) {
        // printf("get %d\n", idx);
        if(vals[idx].second.empty())
            return vals[idx].first;
        int ret = 0;
        for(auto &it: vals[idx].second)
            ret += getVal(it.first) * it.second;
        return ret;
    }
    
public:
    Excel(int height, char width) {
        r = height;
        c = width - 'A' + 1;
        vector<pair<int, map<int, int> > >(r * c).swap(vals);
    }
    
    void set(int row, char column, int val) {
        int idx = (row - 1) * c + (column - 'A');
        vals[idx].first = val;
        vals[idx].second.clear();
    }
    
    int get(int row, char column) {
        int idx = (row - 1) * c + (column - 'A');
        return getVal(idx);
    }
    
    int sum(int row, char column, vector<string> numbers) {
        int idx = (row - 1) * c + (column - 'A'), tmp;
        auto &mp = vals[idx].second;
        mp.clear();
        for(auto &it: numbers) {
            auto jt = it.find(':');
            if(jt == string::npos) {
                tmp = (stoi(it.substr(1)) - 1) * c + (it[0] - 'A');
                ++mp[tmp];
                continue;
            }
            int xL = stoi(it.substr(1, jt - 1)) - 1, xR = stoi(it.substr(jt + 2)) - 1;
            int yL = it[0] - 'A', yR = it[jt + 1] - 'A';
            for(int x = xL; x <= xR; ++x)
                for(int y = yL; y <= yR; ++y)
                    ++mp[x * c + y];
        }
        return getVal(idx);
    }
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel* obj = new Excel(height, width);
 * obj->set(row,column,val);
 * int param_2 = obj->get(row,column);
 * int param_3 = obj->sum(row,column,numbers);
 */
