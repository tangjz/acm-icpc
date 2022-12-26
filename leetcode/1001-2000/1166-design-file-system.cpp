class FileSystem {
    unordered_map<string, int> paths;
    vector<string_view> split(string_view s, char sep = '.') {
        int n = s.size();
        vector<string_view> ret;
        for(int i = 0; i < n; ++i) {
            int j = i;
            for( ; i < n && s[i] != sep; ++i);
            ret.push_back(s.substr(j, i - j));
        }
        if(!s.empty() && s.back() == sep)
            ret.push_back(s.substr(s.size()));
        return move(ret);
    }
public:
    FileSystem() {

    }

    bool createPath(string path, int value) {
        if(path.front() != '/' || path.back() == '/')
            return 0;
        string_view pat = path;
        vector<string_view> items = split(pat.substr(1), '/');
        int len = 0;
        for(auto &item: items) {
            len += 1 + item.size();
            if(len < path.size() && !paths.count((string)pat.substr(0, len)))
                return 0;
        }
        if(paths.count(path))
            return 0;
        paths[path] = value;
        return 1;
    }

    int get(string path) {
        auto it = paths.find(path);
        return it == paths.end() ? -1 : it -> second;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */
