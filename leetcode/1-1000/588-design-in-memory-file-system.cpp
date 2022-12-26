class FileSystem {
    map<string, string> con;
    map<string, set<string> > sub;
public:
    FileSystem() {
        con.clear();
        sub.clear();
        sub[""] = {};
    }

    vector<string> ls(string path) {
        if(path.back() == '/')
            path.pop_back();
        auto it = con.find(path);
        if(it != con.end()) {
            auto jt = path.rfind('/');
            return {path.substr(jt + 1)};
        }
        auto &jt = sub[path];
        return vector<string>(jt.begin(), jt.end());
    }

    void mkdir(string path) {
        sub[path] = {};
        while(path != "") {
            auto it = path.rfind('/');
            string pre = path.substr(0, it), suf = path.substr(it + 1);
            sub[pre].insert(suf);
            path = move(pre);
        }
    }

    void addContentToFile(string filePath, string content) {
        auto it = filePath.rfind('/');
        string pre = filePath.substr(0, it), suf = filePath.substr(it + 1);
        sub[pre].insert(suf);
        con[filePath] += content;
    }

    string readContentFromFile(string filePath) {
        return con[filePath];
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */
