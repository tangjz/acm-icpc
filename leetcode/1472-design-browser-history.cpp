class BrowserHistory {
    int pos;
    vector<string> his;
public:
    BrowserHistory(string homepage) {
        vector<string>().swap(his);
        his.push_back(homepage);
        pos = 0;
    }
    
    void visit(string url) {
        his.resize(pos + 1);
        his.push_back(url);
        ++pos;
    }
    
    string back(int steps) {
        pos = max(pos - steps, 0);
        return his[pos];
    }
    
    string forward(int steps) {
        pos = min(pos + steps, (int)his.size() - 1);
        return his[pos];
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
