class Logger {
    static const int delta = 10;
    unordered_map<string, int> his;
public:
    Logger() {
        unordered_map<string, int>().swap(his);
    }
    
    bool shouldPrintMessage(int timestamp, string message) {
        auto it = his.find(message);
        if(it != his.end() && timestamp - (it -> second) < delta)
            return 0;
        his[message] = timestamp;
        return 1;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
