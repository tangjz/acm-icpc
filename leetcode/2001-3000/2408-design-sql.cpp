class SQL {
    unordered_map<string, pair<int, vector<vector<string> > > > mp;
public:
    SQL(vector<string>& names, vector<int>& columns) {
        int n = names.size();
        for(int i = 0; i < n; ++i)
            mp[names[i]] = {columns[i], {}};
    }
    
    void insertRow(string name, vector<string> row) {
        mp[name].second.push_back(row);
    }
    
    void deleteRow(string name, int rowId) {
        mp[name].second[rowId - 1].clear();
    }
    
    string selectCell(string name, int rowId, int columnId) {
        auto &row = mp[name].second[rowId - 1];
        assert(!row.empty());
        return row[columnId - 1];
    }
};

/**
 * Your SQL object will be instantiated and called as such:
 * SQL* obj = new SQL(names, columns);
 * obj->insertRow(name,row);
 * obj->deleteRow(name,rowId);
 * string param_3 = obj->selectCell(name,rowId,columnId);
 */
