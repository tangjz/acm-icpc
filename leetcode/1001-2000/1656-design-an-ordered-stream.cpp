class OrderedStream {
    int pos;
    vector<string> seq;
public:
    OrderedStream(int n) {
        pos = 0;
        vector<string>(n).swap(seq);
    }
    
    vector<string> insert(int idKey, string value) {
        seq[idKey - 1] = value;
        vector<string> ret;
        for( ; pos < seq.size() && seq[pos] != ""; ++pos)
            ret.push_back(seq[pos]);
        return ret;
    }
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(idKey,value);
 */
